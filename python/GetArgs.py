import sys

class getargs:
    def __init__(self, Args):
        self.sysargs = self.filterArgs(sys.argv)
        self.usrargs = self.filterArgs(Args)
        self.results = self.setSize(self.usrargs)
        self.processResult()

    def filterArgs(self, arguments):
        sysargs = arguments

        args = []
        temp = []
        for i in range(len(sysargs)):
            if sysargs[i][:1] == '-':
                temp = []
                temp.append(sysargs[i])
                for j in range(len(sysargs)):
                    if j == 0:
                        continue
                    k = j + i
                    if k < len(sysargs) and sysargs[k][:1] != '-':
                        temp.append(sysargs[k])
                    else:
                        break
                args.append(temp)
        return args

    def setSize(self, otherlist):
        result = []
        temp = []

        for i in range(len(otherlist)):
            for j in range(len(otherlist[i])):
                temp.append('')
            result.append(temp)
            temp = []
        return result

    def getargs(self):



        result = {}
        for i in range(len(self.results)):
            if self.results[i][0] != '':
                for j in range(len(self.results[i])):
                    result[self.usrargs[i][j]] = self.results[i][j]
        return result


    def processResult(self):
        for i in range(len(self.sysargs)):
            a = self.sysargs[i]

            tally = 0
            for j in range(len(self.usrargs)):
                b = self.usrargs[j]

                if a[0] == b[0]:
                    tally = 1

                    if len(a) == len(b):
                        self.results[j] = self.sysargs[i]
                    else:
                        raise Exception('Argument \'' + a[0] + '\' is being used incorrectly.  Please refer to --help for more information')

                    self.results[j][0] = 'yes'
            if tally == 0:
                raise Exception("Unknown Argument. Please refer to --help for more information")

#-------------------------------------------------------------------------------
# def main():
#     myargs = getargs(['-pull','usrname','pword','-o','-h', '--help'])

#     args = myargs.getargs()

#     if '-o' in args:



# if __name__ == "__main__":
#     main()
