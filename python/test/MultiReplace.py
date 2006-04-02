import tst
import cStringIO

def MultiReplaceWithDict(replace_dict):
    t = tst.TST()
    for k,v in replace_dict.iteritems():
        t[k] = v
    return MultiReplaceWithTST(t)

def MultiReplaceWithTST(t):
    def replace(input_string):
        output = cStringIO.StringIO()
        for source_string, status, replace_with in t.scan_with_stop_chars(input_string,' \t\r\n',tst.TupleListAction()):
            if status>0:
                output.write(replace_with)
            else:
                output.write(source_string)
        return output.getvalue()
    return replace

test_replace = MultiReplaceWithDict({
    'bonjour'  : 'hello',
    'le monde' : 'world',
    'monde'    : 'everybody',
})

print test_replace('bonjour le monde !')
print test_replace('bonjourle monde !')