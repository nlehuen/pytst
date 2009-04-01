from time import clock
clock() # initialise l'horloge

class Timer(object):
    def __init__(self):
        object.__init__(self)
        self.timings = []
        self.stopped = True
        self.need_computations = True
        
    def start(self):
        assert self.stopped, "This timer has already started"
        self._start = clock()
        self.stopped = False
    
    def stop(self,normalize=1.0):
        assert not self.stopped, "This timer is already stopped"
        timing = (clock() - self._start)*normalize
        self.stopped = True
        self.timings.append(timing)
        self.need_computations = True
        return timing
    
    def update_computations(self):
        if self.timings and self.need_computations:
            st = sorted(self.timings) 
            self.min = st[0]
            self.max = st[-1]
            self.avg = sum(st)/len(st)
            
            if len(st)%2:
                self.med = st[len(st)/2]
            else:
                self.med = (st[len(st)/2]+st[len(st)/2-1])/2.0
            self.need_computations = False
    
    def __str__(self):
        self.update_computations()
        return '(count=%3i,min=%7.4f,med=%7.4f,avg=%7.4f,max=%7.4f)'%(
            len(self.timings),
            self.min,
            self.med,
            self.avg,
            self.max
        )
    
