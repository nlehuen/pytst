try:
    from Levenshtein import distance as _levenshtein
    def levenshtein(a,b):
        if (a is None) or (b is None):
            return 999999
        return _levenshtein(a,b)
except ImportError:
    def levenshtein(a,b):
        """
        Calculates the Levenshtein distance between a and b.
        Optimized version (fewer object allocations and array subscriptions) from :
        http://hetland.org/python/distance.py
        """
        if (a is None) or (b is None):
            return 999999

        n, m = len(a), len(b)
        if n > m:
            # Make sure n <= m, to use O(min(n,m)) space
            a,b = b,a
            n,m = m,n

        previous = range(n+1)
        current = range(n+1)
        rangen = range(1,n+1)
        for i in xrange(1,m+1):
            temp = previous
            previous = current
            current = temp
            current[0]=i

            p0p = previous[0]
            p0c = i
            b0c = b[i-1]
            for j in rangen:
                p1p = previous[j]
                add = p1p+1
                delete = p0c+1
                change = p0p
                if a[j-1] != b0c:
                    change += 1
                if add < change:
                    change = add
                if delete < change:
                    change = delete
                current[j] = change
                p0c=change
                p0p=p1p

        return change
