if __name__ == "__main__":
    import sys
    from time import time
    import linecache
    import glob
    from textindex import textindex
    import traceback
    import linecache
    from mutagen.mp3 import MP3
    import os

    ti = textindex()
    
    try:
        start = time()
        ti.read('mp3.ti')
        print 'Loading time : %.2fs'%(time()-start)
    except:
        traceback.print_exc()
        
        start = time()
        lines = 0

        for root, dirnames, filenames in os.walk(sys.argv[1]):
            for filename in filenames:
                if filename[-4:].lower() == '.mp3':
                    try:
                        full_filename = os.path.join(root,filename) 
                        mp3 = MP3(full_filename)
                        title = mp3.get('TIT2')
                        artist = mp3.get('TPE2') 
                        album = mp3.get('TALB')
                        if title:
                            title = title.text[0].decode('iso-8859-1').lower()
                            ti.put_text(title,full_filename)
                        else:
                            ti.put_text(filename[:-4].lower(),mp3)
                        if artist:
                            artist = artist.text[0].decode('iso-8859-1').lower()
                            ti.put_text(artist,full_filename)
                        if album:
                            album = album.text[0].decode('iso-8859-1').lower()
                            ti.put_text(album,full_filename)
                        print title, album, artist
                    except:
                        pass

        ti.pack()
        print 'Indexing time : %.2fs for %i lines'%(time()-start,lines)

        ti.write('mp3.ti')
    
    def lines(text,intersection=True):
        for ln, r in ti.find_text(text.lower(),intersection):
            print '%02i:%s'%(
                r,
                ln
            ),

    def ilines(text,intersection=True):
        for ln, r in ti.find_text(text.lower(),intersection):
            print '%02i:%s'%(
                r,
                ln,
            ),

    if len(sys.argv)>1 and sys.argv[-1]=='gui':
        from Tkinter import *
        class Explorer(object):
            def __init__(self,master):
                self.frame = Frame(master)
                self.frame.pack(fill=BOTH, expand=1)
                
                self.entry = Entry(self.frame, name='input')
                self.entry.pack(fill=X)
                self.entry.bind('<KeyRelease>',self.keyPressed)
                
                frame = Frame(self.frame)
                frame.pack(fill=BOTH, expand=1)
                scrollbar = Scrollbar(frame, orient=VERTICAL)
                self.list = Listbox(frame, name='list', yscrollcommand=scrollbar.set)
                scrollbar.config(command=self.list.yview)
                scrollbar.pack(side=RIGHT, fill=Y)
                self.list.pack(side=LEFT, fill=BOTH, expand=1)
                
                self.label = Label(self.frame, name='count')
                self.label.pack()
            
            def keyPressed(self,event):
                self.list.delete(0,END)
                start = time()
                result = ti.find_text(self.entry.get().lower(),True)
                # result.sort(key=lambda i : -i[1])
                elapsed = time() - start
                for ln, r in result[:100]:
                    self.list.insert(END,'%02i:%s'%(
                        r,
                        ln
                    ))
                self.label.config(text = '%i lines in %.2fs'%(
                    len(result),
                    elapsed
                ))
                
        root = Tk()
        explorer = Explorer(root)
        root.mainloop()
