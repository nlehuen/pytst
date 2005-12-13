import textindex
t = textindex.textindex()

print t.put('nicolas','nicolas')
print t.put('nicolo','nicolas')
print t.put('nico','nico')

print t.find('nico')