import traceback
import ctypes
import sys
import codecs
import itertools
import operator
so = ctypes.cdll.LoadLibrary
lib = so("./suffixarray.so")
def get_data(lines):
	for line in lines:
		line = line.strip().split('\t')
		yield line
for poi,data in itertools.groupby(get_data(sys.stdin),operator.itemgetter(0)):
    try:
        data = list(data)
        if len(data) == 1:
            if len(data[0])<2:
                continue
            print data[0][0]+'\t'+data[0][1]+'\t'+str(len(data[0][1].decode('utf-8')))+'\t1\t1\t1.0'
            continue
	f = codecs.open("pow.in",'w','utf-8')
	f.write(str(len(data)) + '\r\n')
	flag=False
        ssidcnt = 0
        for g in data:
                 if len(g) < 2:
                     continue
		 flag = True
                 ssidcnt += 1
                 if ssidcnt>2500:
                     break
                 ssid = g[1].decode('utf-8')
		 ssidlen = len(ssid)
		 f.write(str(ssidlen) + ' ')
		 for w in ssid:
                        if ord(w)>0xff00:
                            f.write(str(ord('?'))+' ')
                        else:
                            if w>='A' and w<='Z':
                                w = w.lower()
		 	    f.write(str(ord(w))+' ')
		 f.write('\r\n')
	f.close()
        if flag==False:
            continue
	lib.solve()
	f_res = codecs.open("pow.out",'r')
	res = []
        i = -1
        rank = []
	for line in f_res:
                i += 1
                if i == 0:
                    rank = line.strip().split('\t')
                else:
		    line = line.strip().split('\t')
		    res.append((line[0],line[1],line[2]))
#	res = sorted(res,key=lambda d:int(d[0])*int([1]),reverse=True)
	res.sort(key=lambda d:int(d[0])*int(d[1]),reverse=True)
	reslen = int(res[0][0])
        if reslen==0:
            print poi+'\tnone\t0\t0\t'+str(cnt)+'\t0.0'
            continue
        if reslen == 1:
            print poi + '\t' + data[0][1]+'\t'+str(len(data[0][1].decode('utf-8')))+'\t1\t'+str(ssidcnt)+'\t'+str(float(1)/ssidcnt)
            continue
        idx = rank.index(res[0][2])
        cnt = 0
        resstr = ''
        for g in data:
            ssid = g[1].decode('utf-8')
            if idx>=cnt and idx < cnt+len(ssid):
                idx -=cnt
                for i in range(0,reslen):
                    if i+idx<len(ssid):
                        resstr += ssid[i+idx]
                break
            cnt += len(ssid)+1
        print poi+'\t'+resstr.encode('utf-8')+'\t'+str(reslen)+'\t'+res[0][1]+'\t'+str(ssidcnt)+'\t'+str(float(float(res[0][1])/ssidcnt))
    except:
       # pass
        traceback.print_exc() 
