# -*- coding: iso-8859-1 -*-
import psyco
psyco.full()

from array import array
import sys

# Tant qu'à faire vu qu'ici le nombre de caractères par noeud est complètement
# dynamique, on peut se lâcher, mettre 1024 caractère ou plus
CHARS_PER_NODE = 16

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
            
            if local_index < len(node.chars) - 1:
                # on s'est arrêté avant le dernier caractère du noeud,
                # il n'y a donc pas de match possible (sinon il y aurait eu
                # split à l'insertion)
                return None
            
            elif local_index == len(node.chars) - 1:
                # différence au dernier caractère du noeud
                # on va donc aller soit à droite, soit à gauche
                if diff>0:
                    node = node.left
                elif diff<0:
                    node = node.right
                else:
                    node = node.next
            else:
                # tous les caractères du noeud correspondent à ceux de la chaîne
                if index == len(string):
                    # si on est en fin de chaîne, on retourne la donnée stockée
                    # dans le noeud, si elle existe
                    return node.data
                else:
                    # sinon, on passe au noeud suivant
                    node = node.next
        
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
                assert balance.height == self._compute_balance(node).height

            # Maintenant que le split est fait, on peut continuer à positionner
            # la nouvelle clé
            balance = balance_info()
            if diff>0:
                node.left, left_balance = self._insert(string,value,index,node.left)
                assert not (len(node.left.chars)>1 and left_balance.height!=1)
                balance.did_balance = left_balance.did_balance
                right_balance = self._compute_balance(node.right)
            else:
                node.right, right_balance = self._insert(string,value,index,node.right)
                assert not (len(node.right.chars)>1 and right_balance.height!=1)
                balance.did_balance = right_balance.did_balance
                left_balance = self._compute_balance(node.left)

            # On calcule la nouvelle balance en tenant compte des modifs
            balance.height = (len(node.chars)>1 and 1) or max(left_balance.height, right_balance.height) + 1
            balance.balance = left_balance.height - right_balance.height
            balance.left_balance = left_balance.balance
            balance.right_balance = right_balance.balance

            assert balance.height == self._compute_balance(node).height

            if not balance.did_balance:
                # On effectue la balance si elle n'a pa déjà été effectué
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
        
            return node, self._compute_balance(node)

        else:
            # On est arrivé au bout de la clé, mais pas au bout des caractères
            # du noeud
            assert index == len(string)
            
            # On est au bout de la clé, mais avant la fin des caractères du
            # noeud ; il faut donc splitter, mais au local_index précédent car
            # on a bêtement avancé les deux à la fois aux lignes 105 - 106 
            node, balance = self._split_node(node,local_index-1)

            # On stocke ensuite la clé et la valeur
            node.data = value
            
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

        assert -2 < balance.balance < 2
        assert -2 < self._compute_balance(node).balance < 2

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
        left_node.right, discard = self._cat_node(left_node.right,None)

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

        right_node.left, discard = self._cat_node(right_node.left,None)

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

    def _cat_node(self,node,balance):
        """ Tente de ressouder un noeud à son noeud suivant si cela est
            possible """
        if node is None:
            return None
        elif (node.next is not None
            and node.left is None and node.right is None
            and node.data is None
            and len(node.chars)+len(node.next.chars)<CHARS_PER_NODE
        ):
            # Les quatre conditions ci dessus sont :
            # - on a un noeud suivant
            # - le noeud actuel n'est pas un pivot (dans ce cas la concaténation
            # serait impossible)
            # - le noeud actuel ne contient pas de données (idem)
            # - il y a de la place pour les caractères du noeud courant dans
            # le noeud suivant
            node.chars.extend(node.next.chars)
            node.next.chars = node.chars
            return node.next, balance_info(height=1)
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
    
    def stats(self,node,acc):
        if node == None : return
        
        acc['nodes'] = acc.get('nodes',0) + 1
        key = ('nbchars',len(node.chars)) 
        acc[key] = acc.get(key,0) + 1
        
        links = ((node.left is not None and 1) or 0) + ((node.next is not None and 1) or 0) + ((node.right is not None and 1) or 0) 
        key = ('links',links)
        acc[key] = acc.get(key,0) + 1
        
        self.stats(node.left,acc)
        self.stats(node.next,acc)
        self.stats(node.right,acc)
        
        return acc
        
if __name__ == '__main__':
    urls = compact_tst()
    try:
        chars = 0
        for n, l in enumerate(file('url_1000000.csv','rb')):
            if n == 100000: break
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
                100.0 * stats[key] / stats['nodes']
            ) 

    for n, l in enumerate(file('url_1000000.csv','rb')):
        if n == 100000: break
        if n%1000==0 : print 'Check ',n
        key = l.rstrip()
        assert urls[key] == 0

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
    
    data = range(10000)
    random.shuffle(data)
    
    for i, d in enumerate(data):
        if i%1000==0: print i
        t[str(d)] = d
#         for i2, d2 in enumerate(data[:i]):
#             assert t[str(d2)] == d2
        
    
    for i,d in enumerate(data):
        assert t[str(d)] == d, "%s => %s != %s"%(d,i,t[str(d)]) 
