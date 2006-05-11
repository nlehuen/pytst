# -*- coding: iso-8859-1 -*-
from array import array
import sys

CHARS_PER_NODE = 1024



class tst_node(object):
    def __init__(self):
        self.number_of_chars = 0
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
            while local_index < node.number_of_chars and index < len(string):
                diff = cmp(string[index],node.chars[local_index]) 
                if diff == 0:
                    local_index += 1
                    index += 1
                else:
                    break
            
            if local_index < node.number_of_chars - 1:
                # on s'est arrêté avant le dernier caractère du noeud,
                # il n'y a donc pas de match possible (sinon il y aurait eu
                # split à l'insertion)
                return None
            elif local_index == node.number_of_chars - 1:
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
        assert self[string] == value, "%s : %s != %s"%(string,value,self[string])

    def _insert(self,string,value,index,node):
        if node is None:
            return self._new_node(string,value,index)
    
        local_index = 0
        
        # On avance tant qu'il y a égalité
        diff = 0
        while local_index < node.number_of_chars and index<len(string):
            diff = cmp(string[index],node.chars[local_index])
            if diff == 0:
                local_index += 1
                index += 1
            else:
                break
        
        if local_index < node.number_of_chars-1:
            # On a trouvé un point de divergence avant la fin des caractères du
            # noeud, il va donc falloir splitter
            
            # On crée un nouveau noeud
            new_node = tst_node()
            
            # On prend tout le début du segment de clé du noeud jusqu'à y compris
            # le caractère qui diffère et on les met dans le nouveau noeud
            new_node.number_of_chars = local_index + 1
            new_node.chars = node.chars[0:local_index + 1]

            # La suite de ce nouveau noeud est l'ancien noeud
            new_node.next = node

            # On adapte la chaîne dans l'ancien noeud, c'est le restant de
            # la chaîne après le split
            node.number_of_chars = node.number_of_chars - local_index - 1
            node.chars = node.chars[local_index + 1:]
            
            # Maintenant que le split est fait, on peut continuer à positionner
            # la nouvelle clé
            if diff>0:
                new_node.left = self._new_node(string,value,index)
            elif diff<0:
                new_node.right = self._new_node(string,value,index)
            else:
                assert index == len(string)
                new_node.key = string
                new_node.data = value

            return new_node

        elif local_index == node.number_of_chars-1:
            # Il y a divergence au dernier caractère, pas besoin de splitter
            if diff>0:
                node.left = self._insert(string,value,index,node.left)
            elif diff<0:
                node.right = self._insert(string,value,index,node.right)
            else:
                assert index == len(string)
                node.key = string
                node.data = value
            
            return node

        elif local_index == node.number_of_chars:
            assert diff == 0
            
            # On est arrivé au bout des caractères du noeud
            if index==len(string):
                # si on est en fin de chaîne, on stocke la donnée
                node.key = string
                node.data = value
                return node
            else:
                # on n'est pas en fin de chaîne, on continue
                node.next = self._insert(string,value,index,node.next)
                return node

    def _new_node(self,string,value,index):
        length = min(len(string)-index,CHARS_PER_NODE)

        new_node = tst_node()
        new_node.number_of_chars = length
        # On remplit le segment du noeud avec les caractères
        new_node.chars.extend(string[index:index+length])
        
        if index+length<len(string):
            # s'il reste des caractères dans la clé après ce segment...
            new_node.next = self._new_node(string,value,index+length)
        else:
            # sinon on met la clé et la donnée dans ce noeud
            new_node.key = string
            new_node.data = value
        
        return new_node
        
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
        print i,d
        t[str(d)] = i
#        for j, d2 in enumerate(data[:i]):
#            assert t[str(d2)] == j, "%s=%s ! %s => %s != %s"%(d,i,d2,j,t[str(d2)])
    
    for i,d in enumerate(data):
        assert t[str(d)] == i, "%s => %s != %s"%(d,i,t[str(d)]) 
