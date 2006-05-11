# -*- coding: iso-8859-1 -*-
from array import array
import sys

CHARS_PER_NODE = 1024



class tst_node(object):
    __slots__ = ['chars','key','data','next','left','right']

    def __init__(self):
        self.chars = array('c')
        self.key = None # inutile, just là pour le debug
        self.data = None
        self.next = None
        self.left = None
        self.right = None
    
    def __repr__(self):
        return "node(%s,key=%s,data=%s,%i,%i,%i)"%(
            self.chars,
            self.key,
            self.data,
            self.left is not None and 1 or 0,
            self.next is not None and 1 or 0,
            self.right is not None and 1 or 0,
        )

class compact_tst(object):
    def __init__(self):
        self.root = None

    def __getitem__(self,string):
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
        self.root = self._insert(string,value,0,self.root)
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
                node = self._split_node(node,local_index)
            
            # Maintenant que le split est fait, on peut continuer à positionner
            # la nouvelle clé
            if diff>0:
                node.left = self._insert(string,value,index,node.left)
            else:
                node.right = self._insert(string,value,index,node.right)

            # Puisqu'on vient d'effectuer une opération qui a pu perturber
            # l'équilibre du noeud, on le rétablit. Bien sûr cela peut changer
            # le noeud devant être retourné à l'appelant.
            node = self._balance_node(node)

            return node

        elif local_index == len(node.chars):
            # On est arrivé au bout des caractères du noeud
            # sans différence
            
            if index == len(string):
                # On est également au bout de la clé
                # C'est qu'on a de la chance !
                node.key = string
                node.data = value
            else:
                # On n'est pas au bout de la clé
                node.next = self._insert(string,value,index,node.next)
        
            return node

        else:
            # On est arrivé au bout de la clé, mais pas au bout des caractères
            # du noeud
            assert index == len(string)
            
            # On est au bout de la clé, mais avant la fin des caractères du
            # noeud ; il faut donc splitter, mais au local_index précédent car
            # on a bêtement avancé les deux à la fois aux lignes 95-96 
            node = self._split_node(node,local_index-1)

            # On stocke ensuite la clé et la valeur
            node.key = string
            node.data = value
            
            return node

    def _split_node(self,node,local_index):
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
        
        return new_node

    def _new_node(self,string,value,index):
        new_node = tst_node()

        # On remplit le segment du noeud avec un maximum de caractères de la clé
        # en partant de l'index donné
        length = min(len(string)-index,CHARS_PER_NODE)
        new_node.chars.extend(string[index:index+length])
        
        if index+length<len(string):
            # s'il reste des caractères dans la clé après ce segment...
            new_node.next = self._new_node(string,value,index+length)
        else:
            # sinon on met la clé et la donnée dans ce noeud
            new_node.key = string
            new_node.data = value
        
        return new_node
    
    def _balance_node(self,node):
        # ici vérifier le critère AVL et faire une rotation LL, RR, RL ou LR
        # si nécessaire
        return node
        
if __name__ == '__main__':
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
    
    data = range(100000)
    random.shuffle(data)
    
    for i, d in enumerate(data):
        t[str(d)] = i
    
    for i,d in enumerate(data):
        assert t[str(d)] == i, "%s => %s != %s"%(d,i,t[str(d)]) 
