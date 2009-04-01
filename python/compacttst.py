# -*- coding: iso-8859-1 -*-
from array import array
import sys

# Tant qu'à faire vu qu'ici le nombre de caractères par noeud est complètement
# dynamique, on peut se lâcher, mettre 1024 caractère ou plus
CHARS_PER_NODE = 1024

class tst_node(object):
    """ classe représentant un noeud du TST """

    # __slots__ est une optimisation permettant de créer des objets Python
    # non dynamiques, ce qui utilise moins de mémoire
    __slots__ = ['chars','data','next','left','right']

    instances = 0

    def __init__(self):
        tst_node.instances += 1
        self.chars = array('c')
        self.data = None
        self.next = None
        self.left = None
        self.right = None
    
    def __repr__(self):
        return "node(%s,data=%s,%i,%i,%i)"%(
            self.chars,
            self.data,
            self.left is not None and 1 or 0,
            self.next is not None and 1 or 0,
            self.right is not None and 1 or 0,
        )

class balance_info(object):
    __slots__ = ['did_balance','height','balance','right_balance','left_balance']
    
    def __init__(self,did_balance=False,height=0,balance=0,right_balance=0,left_balance=0):
        self.did_balance = did_balance
        self.height = height
        self.balance = balance
        self.right_balance = right_balance
        self.left_balance = left_balance

    def __repr__(self):
        return "balance_info(d=%s,h=%s,b=%s,l=%s,r=%s)"%(
            self.did_balance,
            self.height,
            self.balance,
            self.left_balance,
            self.right_balance
        )

class compact_tst(object):
    """ Implémentation d'un TST compact """

    def __init__(self):
        self.root = None

    def __getitem__(self,string):
        """ Lit dans l'arbre selon la syntaxe tst[string] """
        
        # ATTENTION : ce code est intentionnellement dupliqué dans la méthode
        # visit(). Ne pas oublier de mettre celle-ci à jour lorsqu'il est modifié
        # ici.
        
        node = self.root
        index = 0
        while node is not None:
            local_index = 0
    
            # On avance tant qu'il y a égalité
            diff = 0
            while local_index < len(node.chars) and index < len(string):
                diff = cmp(string[index],node.chars[local_index]) 
                if diff == 0:
                    local_index += 1
                    index += 1
                else:
                    break
            
            if diff != 0:
                # On a une différence de caractère
                
                if local_index < len(node.chars) - 1:
                    # on s'est arrêté avant le dernier caractère du noeud,
                    # il n'y a donc pas de match possible (sinon il y aurait eu
                    # split à l'insertion)
                    return None
                elif diff>0:
                        node = node.left
                else: # diff<0
                    node = node.right
    
            elif local_index == len(node.chars):
                # On est au bout des caractères du noeud
            
                if index == len(string):
                    # On est également au bout de la clé
                    # C'est qu'on a de la chance !
                    return node.data
                else:
                    # On avance d'un cran
                    node = node.next

            else:
                # On n'est pas au bout des caractères, c'est qu'on est au
                # bout de la clé, et donc qu'il n'y a pas de match, sinon
                # il y aurait eu un split
                assert index == len(string)
                return None
        
        # node is None ==> pas de match
        return None

    
    def __setitem__(self,string,value):
        """ Ecrit dans l'arbre selon la syntaxe tst[string] = value """
        self.root, discard = self._insert(string,value,0,self.root)
        assert self[string] == value

    def _insert(self,string,value,index,node):
        if node is None:
            return self._new_node(string,value,index)
    
        local_index = 0
        
        # On avance tant qu'il y a égalité
        diff = 0
        while local_index < len(node.chars) and index<len(string):
            diff = cmp(string[index],node.chars[local_index])
            if diff == 0:
                local_index += 1
                index += 1
            else:
                break
        
        if diff!=0:
            assert local_index < len(node.chars) and index<len(string)
        
            # On a trouvé un point de divergence avant le dernier caractère du
            # noeud, et de la clé, il va donc falloir splitter
            if local_index < len(node.chars) - 1:
                node, balance = self._split_node(node,local_index)
                # On peut essayer de joindre le noeud suivant au noeud d'après
                # car le split peut permettre de compléter un noeud pas totalement
                # remplit
                node.next, discard = self._compact_node(node.next,None)

            # Maintenant que le split est fait, on peut continuer à positionner
            # la nouvelle clé
            balance = balance_info()
            if diff>0:
                node.left, left_balance = self._insert(string,value,index,node.left)
                balance.did_balance = left_balance.did_balance
                right_balance = self._compute_balance(node.right)
            else:
                node.right, right_balance = self._insert(string,value,index,node.right)
                balance.did_balance = right_balance.did_balance
                left_balance = self._compute_balance(node.left)

            # On calcule la nouvelle balance en tenant compte des modifs
            if len(node.chars)>1:
                balance.height = 1
            else:
                balance.height = max(left_balance.height, right_balance.height) + 1
            balance.balance = left_balance.height - right_balance.height
            balance.left_balance = left_balance.balance
            balance.right_balance = right_balance.balance

            if not balance.did_balance:
                # On effectue la balance si elle n'a pas déjà été effectuée
                node, balance = self._balance(node,balance)

                if len(node.chars)!=1:
                    # Si à l'issue de la balance on se retrouve avec plusieurs
                    # caractères, alors la hauteur du nouveau noeud est 1.
                    balance.height = 1
                    balance.balance = 0
                    balance.left_balance = 0
                    balance.right_balance = 0

            return node, balance

        elif local_index == len(node.chars):
            # On est arrivé au bout des caractères du noeud
            # sans différence
            
            if index == len(string):
                # On est également au bout de la clé
                # C'est qu'on a de la chance !
                node.data = value
            else:
                # On n'est pas au bout de la clé
                node.next, next_balance = self._insert(string,value,index,node.next)
        
                # Suite à un split du noeud suivant, il est peut-être possible
                # de le recoller à ce noeud ?
                node, discard = self._compact_node(node, None)
        
            return node, self._compute_balance(node)

        else:
            # On est arrivé au bout de la clé, mais pas au bout des caractères
            # du noeud
            assert index == len(string)
            
            # On est au bout de la clé, mais avant la fin des caractères du
            # noeud ; il faut donc splitter, mais au local_index précédent car
            # on a bêtement avancé les deux à la fois aux lignes 105 - 106 
            node, balance = self._split_node(node,local_index-1)

            # On peut essayer de joindre le noeud suivant au noeud d'après
            node.next, discard = self._compact_node(node.next,None)

            # On stocke ensuite la clé et la valeur
            node.data = value
            
            return node, balance

    def __delitem__(self,string):
        self.root, discard = self._remove(string,0,self.root)

    def _remove(self,string,index,node):
        if node is None:
            return None
    
        local_index = 0
        
        # On avance tant qu'il y a égalité
        diff = 0
        while local_index < len(node.chars) and index<len(string):
            diff = cmp(string[index],node.chars[local_index])
            if diff == 0:
                local_index += 1
                index += 1
            else:
                break
        
        if diff!=0:
            assert local_index < len(node.chars) and index<len(string)
        
            # On a trouvé un point de divergence avant le dernier caractère du
            # noeud, et de la clé, il va donc falloir splitter
            if local_index < len(node.chars) - 1:
              return node, self._compute_balance(node)
              
            # Maintenant que le split est fait, on peut continuer à positionner
            # la nouvelle clé
            balance = balance_info()
            if diff>0:
                node.left, left_balance = self._remove(string,index,node.left)
                balance.did_balance = left_balance.did_balance
                node, balance = self._compact_node(node,balance,True)
                right_balance = self._compute_balance(node.right)
            else:
                node.right, right_balance = self._remove(string,index,node.right)
                balance.did_balance = right_balance.did_balance
                node, balance = self._compact_node(node,balance,True)
                left_balance = self._compute_balance(node.left)

            # On calcule la nouvelle balance en tenant compte des modifs
            if len(node.chars)>1:
                balance.height = 1
            else:
                balance.height = max(left_balance.height, right_balance.height) + 1
            balance.balance = left_balance.height - right_balance.height
            balance.left_balance = left_balance.balance
            balance.right_balance = right_balance.balance

            if not balance.did_balance:
                # On effectue la balance si elle n'a pas déjà été effectuée
                node, balance = self._balance(node,balance)

                if len(node.chars)!=1:
                    # Si à l'issue de la balance on se retrouve avec plusieurs
                    # caractères, alors la hauteur du nouveau noeud est 1.
                    balance.height = 1
                    balance.balance = 0
                    balance.left_balance = 0
                    balance.right_balance = 0

            # return self._compact_node(node,balance)
            return node, balance

        elif local_index == len(node.chars):
            # On est arrivé au bout des caractères du noeud
            # sans différence
            
            if index == len(string):
                # On est également au bout de la clé
                # C'est qu'on a de la chance !
                node.data = None
            else:
                # On n'est pas au bout de la clé
                node.next, next_balance = self._remove(string,index,node.next)
        
                # Suite à un split du noeud suivant, il est peut-être possible
                # de le recoller à ce noeud ?
                # node, discard = self._compact_node(node, None)
        
            return self._compact_node(node,self._compute_balance(node))

        else:
            # On est arrivé au bout de la clé, mais pas au bout des caractères
            # du noeud
            assert index == len(string)
            
            # On est au bout de la clé, mais avant la fin des caractères du
            # noeud 
            
            return node, balance

    def _compute_balance(self,node):
        
        if node is not None:
            if len(node.chars)>1:
                # La hauteur d'un noeud contenant plusieurs caractères
                # est forcément 1
                return balance_info(height=1)
            else:
                balance = balance_info()

                # Récursion sur les noeuds fils
                left_balance = self._compute_balance(node.left)
                right_balance = self._compute_balance(node.right)
    
                balance.did_balance = False
                balance.height = max(left_balance.height, right_balance.height) + 1
                balance.balance = left_balance.height - right_balance.height
                balance.left_balance = left_balance.balance
                balance.right_balance = right_balance.balance
                
                return balance
        else:
            # La hauteur d'un noeud non existant est 0, ce qui fait
            # que la hauteur d'une feuille est 1
            return balance_info()

    def _balance(self,node,balance):
        assert balance.height == self._compute_balance(node).height, (node, balance, self._compute_balance(node))
        assert len(node.chars)>1 or balance.balance == self._compute_balance(node).balance, "%s : %s != %s"%(node,balance,self._compute_balance(node))
        assert balance.left_balance == self._compute_balance(node.left).balance
        assert balance.right_balance == self._compute_balance(node.right).balance

        assert -2 < balance.left_balance < 2
        assert -2 < balance.right_balance < 2
        assert -3 < balance.balance < 3

        assert -2 < self._compute_balance(node.left).balance < 2
        assert -2 < self._compute_balance(node.right).balance < 2
        assert -3 < self._compute_balance(node).balance < 3

        # Assure le critère AVL
        if balance.balance > 1:
            if balance.left_balance > 0:
                node, balance = self._ll(node,balance)
            else:
                node, balance = self._lr(node,balance)
            balance.did_balance = True
        elif balance.balance < -1:
            if balance.right_balance < 0:
                node, balance = self._rr(node,balance)
            else:
                node, balance = self._rl(node,balance)
            balance.did_balance = True

        assert -2 < self._compute_balance(node).balance < 2,(node,self._compute_balance(node)) 
        assert -2 < balance.balance < 2

        return node, balance
    
    def _ll(self,node,balance):
        # Un déséquilibre LL n'est possible qu'avec un noeud de gauche
        # n'ayant qu'un caractère
        assert len(node.left.chars) == 1

        # On fait la rotation au niveau des liens
        left_node = node.left
        node.left = left_node.right
        left_node.right = node
        
        # Et maintenant on ramène tous les caractères du noeud d'origine sauf son
        # dernier, et on les insère au début du noeud de gauche.
        # En gros si dans le noeud d'origine on a abcdefG
        # et dans le noeud de gauche on a juste B
        # A la fin on a dans le noeud d'origine juste G
        # et dans le noeud de gauche abcdefB
        new_char = node.chars.pop()
        node.chars.append(left_node.chars.pop())
        left_node.chars.append(new_char)
        node.chars, left_node.chars = left_node.chars, node.chars
        
        # Il est possible que le noeud d'origine soit concaténable avec la suite
        left_node.right, discard = self._compact_node(left_node.right,None)

        # On ajuste la balance en fonction de l'opération effectuée
        balance.height -= 1
        balance.balance = 0
        balance.left_balance = 0

        # Le noeud de gauche prend la place du noeud d'origine dans l'arbre
        return left_node, balance
         
    def _rr(self,node,balance):
        assert len(node.right.chars) == 1

        right_node = node.right
        node.right = right_node.left
        right_node.left = node
        
        new_char = node.chars.pop()
        node.chars.append(right_node.chars.pop())
        right_node.chars.append(new_char)
        node.chars, right_node.chars = right_node.chars, node.chars 

        right_node.left, discard = self._compact_node(right_node.left,None)

        balance.height -= 1
        balance.balance = 0
        balance.right_balance = 0

        return right_node, balance
    
    def _lr(self,node,balance):
        if len(node.left.right.chars)>1:
            node.left.right, discard = self._split_node(node.left.right,0)
        node.left, discard = self._rr(node.left,balance_info())
        node, balance = self._ll(node,balance)
        return node, balance
    
    def _rl(self,node,balance):
        if len(node.right.left.chars)>1:
            node.right.left, discard = self._split_node(node.right.left,0)
        node.right, discard = self._ll(node.right,balance_info())
        node, balance = self._rr(node,balance)
        return node, balance

    def _split_node(self,node,local_index):
        """ Découpe un noeud à l'index donné """
        assert local_index < len(node.chars)
        
        # On crée un nouveau noeud
        new_node = tst_node()
        
        # On prend tout le début du segment de clé du noeud y compris
        # le caractère qui diffère et on les met dans le nouveau noeud
        new_node.chars = node.chars[0:local_index + 1]

        # La suite de ce nouveau noeud est l'ancien noeud
        new_node.next = node

        # On adapte la chaîne dans l'ancien noeud, c'est le restant de
        # la chaîne après le split
        node.chars = node.chars[local_index + 1:]
        
        return new_node, balance_info(height=1)

    def _compact_node(self,node,balance,debug=False):
        """ Tente de ressouder un noeud à son noeud suivant si cela est
            possible """
        if node is None:
            return None, balance_info()
        elif node.data is not None:
            return node, balance
        elif (
            node.next is not None
            and node.left is None and node.right is None
            and len(node.chars)+len(node.next.chars)<CHARS_PER_NODE
        ):
            # Les quatre conditions ci dessus sont :
            # - on a un noeud suivant
            # - le noeud actuel n'est pas un pivot (dans ce cas la concaténation
            # serait impossible)
            # - le noeud actuel ne contient pas de données (idem)
            # - il y a de la place pour les caractères du noeud courant dans
            # le noeud suivant
            if debug: print "CAT", node, node.next,
            node.chars.extend(node.next.chars)
            node.next.chars = node.chars
            if debug: print '=>',node.next
            return node.next, self._compute_balance(node.next)
        elif (
            node.next is None
            and (node.left is None or node.right is None)
        ):
            if node.left is None and node.right is None:
                if debug: print "CAT2", node, "=>", None
                return None, balance_info()
            else:
                # On prend le noeud restant
                new_node = node.left or node.right
                
                if len(node.chars)+len(new_node.chars) - 1 < CHARS_PER_NODE:
                    if debug: print "CAT3", node, new_node,
                    # On supprime le dernier caractère du noeud
                    node.chars.pop()
                    # On ajoute les caractères du nouveau noeud
                    node.chars.extend(new_node.chars)
                    # On met le résultat dans le nouveau noeud
                    new_node.chars = node.chars
                    if debug: print '=>',new_node
                    return new_node, self._compute_balance(new_node)
                else:
                    return node, balance
        else:
            return node, balance             

    def _new_node(self,string,value,index):
        new_node = tst_node()

        # On remplit le segment du noeud avec un maximum de caractères de la clé
        # en partant de l'index donné
        length = min(len(string)-index,CHARS_PER_NODE)
        new_node.chars.extend(string[index:index+length])
        
        if index+length<len(string):
            # s'il reste des caractères dans la clé après ce segment...
            new_node.next, discard = self._new_node(string,value,index+length)
        else:
            # sinon on met la clé et la donnée dans ce noeud
            new_node.data = value
        
        return new_node, balance_info(height=1)
    
    def stats(self,node,acc,depth=0):
        if node == None : return
        
        acc['nodes'] = acc.get('nodes',0) + 1
        acc['total_chars'] = acc.get('total_chars',0) + len(node.chars)
        key = ('nbchars',len(node.chars)) 
        
        acc[key] = acc.get(key,0) + 1
        
        links = ((node.left is not None and 1) or 0) + ((node.next is not None and 1) or 0) + ((node.right is not None and 1) or 0) 
        key = ('links',links)
        acc[key] = acc.get(key,0) + 1
        
        key = ('depth',depth)
        acc[key] = acc.get(key,0) + 1
        
        self.stats(node.left,acc,depth+1)
        self.stats(node.next,acc,depth+1)
        self.stats(node.right,acc,depth+1)
        
        return acc

    def visit(self,callback,string=None):
        if string is not None:
            # Ce code est copié / collé depuis _find_node().
            # C'est fait exprès, car cela évite d'avoir instanciation d'un
            # tuple pour retour de valeur multiple à chaque appel de __getitem__.
            
            node = self.root
            index = 0
            while node is not None:
                local_index = 0
        
                # On avance tant qu'il y a égalité
                diff = 0
                while local_index < len(node.chars) and index < len(string):
                    diff = cmp(string[index],node.chars[local_index]) 
                    if diff == 0:
                        local_index += 1
                        index += 1
                    else:
                        break
                
                if diff != 0:
                    # On a une différence de caractère
                    
                    if local_index < len(node.chars) - 1:
                        # on s'est arrêté avant le dernier caractère du noeud,
                        # il n'y a donc pas de match possible (sinon il y aurait eu
                        # split à l'insertion)
                        node = None
                        break
                    else:
                        # différence au dernier caractère du noeud
                        if diff>0:
                            node = node.left
                        elif diff<0:
                            node = node.right
        
                elif local_index == len(node.chars):
                    # On est au bout des caractères du noeud
                
                    if index == len(string):
                        # On est également au bout de la clé
                        # C'est qu'on a de la chance !
                        break
                    else:
                        # On avance d'un cran
                        node = node.next
    
                else:
                    # On n'est pas au bout des caractères, c'est qu'on est au
                    # bout de la clé, et donc qu'il n'y a pas de match, sinon
                    # il y aurait eu un split
                    assert index == len(string)
                    # On retourne le noeud quand même car il va être utile pour
                    # le visiteur, simplement il n'y a aucune donnée dedans
                    break
        
            if node is None:
                return False
            else:
                key = string[:len(string)-local_index]
                return self._visit(node,array('c',key),callback,local_index<len(node.chars))
        else:
            return self._visit(self.root,array('c'),callback,True)

    def _visit(self,node,string,callback,visit_left_right):
        if node is None:
            return False
        
        # D'abord à droite pour obtenir un ordre lexicographique
        if visit_left_right and self._visit(node.right,string+node.chars[:-1],callback,True):
            return True

        # Maintenant le noeud en cours
        if node.data is not None and callback(string+node.chars,node.data):
            return True
        
        # Puis le noeud suivant
        if self._visit(node.next,string+node.chars,callback,True):
            return True
        
        # Puis à gauche
        if visit_left_right and self._visit(node.left,string+node.chars[:-1],callback,True):
            return True
        
        return False
        
    def cat(self,node,debug=False):
    	""" Méthode forçant la concaténation des noeuds, inutile sauf en cas de bug. """
        if node == None : return
        node.left = self.cat(node.left,debug)
        node.next = self.cat(node.next,debug)
        node.right = self.cat(node.right,debug)
        node, discard = self._compact_node(node,None,debug)
        return node
    
    def debug(self,node,indentation=0):
        print node.chars,node.data
        if node.left is not None:
            print '  '*(indentation+1),'LEFT',
            self.debug(node.left,indentation+1)
        if node.next is not None:
            print '  '*(indentation+1),'NEXT',
            self.debug(node.next,indentation+1)
        if node.right is not None:
            print '  '*(indentation+1),'RIGHT',
            self.debug(node.right,indentation+1)

if __name__ == '__main__':
    urls = compact_tst()

    def callback(key,value):
        assert urls[key] == value, "%s : %s != %s"%(key,urls[key],value)
        print key, value
        return False

    QUANTITY = 1000 - 1

    n = 0
    try:
        chars = 0
        for n, l in enumerate(file('url_1000000.csv','rb')):
            if n == QUANTITY: break
            if n%1000==0 : print n
            key = l.rstrip()
            chars += len(key)
            urls[key] = 0
    finally:
        stats = {}
        urls.stats(urls.root,stats)
        print n+1, "lignes", chars, "caracteres"
        for key in sorted(stats.keys()):
            print "%16s\t%6i\t%6.2f%%"%(
                key,
                stats[key],
                (key=='total_chars' and 100.0 * stats[key] / chars) or (100.0 * stats[key] / stats['nodes']) 
            ) 

    urls.root = urls.cat(urls.root,True)

	# On recalcule les stats après concaténation forcée des noeuds.
	# Si qqchose a changé c'est un bug !
    stats = {}
    urls.stats(urls.root,stats)
    print n+1, "lignes", chars, "caracteres"
    for key in sorted(stats.keys()):
        print "%16s\t%6i\t%6.2f%%"%(
            key,
            stats[key],
            (key=='total_chars' and 100.0 * stats[key] / chars) or (100.0 * stats[key] / stats['nodes']) 
        ) 

    for n, l in enumerate(file('url_1000000.csv','rb')):
        if n == QUANTITY: break
        if n%1000==0 : print 'Delete ',n
        key = l.rstrip()
        if n%2 == 0 : del urls[key]

    urls.root = urls.cat(urls.root,True)

    for n, l in enumerate(file('url_1000000.csv','rb')):
        if n == QUANTITY: break
        if n%1000==0 : print 'Check ',n
        key = l.rstrip()
        if n%2==1:
            assert urls[key] == 0
        else:
            assert urls[key] is None

	# On recalcule les stats après concaténation forcée des noeuds.
	# Si qqchose a changé c'est un bug !
    stats = {}
    urls.stats(urls.root,stats)
    print n+1, "lignes", chars, "caracteres"
    for key in sorted(stats.keys()):
        print "%16s\t%6i\t%6.2f%%"%(
            key,
            stats[key],
            (key=='total_chars' and 100.0 * stats[key] / chars) or (100.0 * stats[key] / stats['nodes']) 
        ) 

    t = compact_tst()
    t['nicolas'] = 'nicolas'
    t['laurent'] = 'laurent'
    t['nicolas lehuen'] = 'nicolas lehuen'
    t['laurent querel'] = 'laurent querel'
    assert 'nicolas' == t['nicolas']
    assert 'nicolas lehuen' == t['nicolas lehuen']
    assert 'laurent' == t['laurent']
    assert 'laurent querel' == t['laurent querel']
 
    import random
        
    t = compact_tst()
    
    data = range(1000)
    seed = random.randint(-5000000,5000000)
    print 'Seed is ',seed
    seed = 654
    random.Random(seed).shuffle(data)
    
    for i, d in enumerate(data):
        if i%100==0: print i
        t[str(d)] = d
        for i2, d2 in enumerate(data[:i]):
            assert t[str(d2)] == d2
        
    for i, d in enumerate(data):
        if i%100==0: print i
        if i%3==0: del t[str(d)]

    t.root = t.cat(t.root,True)

    for i,d in enumerate(data):
       if i%3==0 :
           assert t[str(d)] == None, "%s => %s != %s"%(d,None,t[str(d)]) 
       else: 
          assert t[str(d)] == d, "%s => %s != %s"%(d,i,t[str(d)]) 
