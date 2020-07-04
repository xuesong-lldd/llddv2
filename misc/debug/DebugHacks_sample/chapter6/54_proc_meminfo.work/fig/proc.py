#!/usr/bin/env python
from ROOT import TTree, TFile
from array import array
import sys, re

if len(sys.argv) < 2:
    print 'Usage'
    print '  $ proc.py filename'
    sys.exit(-1)
ifname = sys.argv[1]
if re.search('\.[^\.]*$', ifname):
  ofname = re.sub('\.[^\.]*$', '', ifname)
else:
  ofname = ifname
ofname += '.root'

memTotal     = array('i', [0])
memFree      = array('i', [0])
buffers      = array('i', [0])
cached       = array('i', [0])
swapCached   = array('i', [0])
active       = array('i', [0])
inactive     = array('i', [0])
lowFree      = array('i', [0])
swapFree     = array('i', [0])
dirty        = array('i', [0])
writeback    = array('i', [0])
anonPages    = array('i', [0])
mapped       = array('i', [0])
slab         = array('i', [0])
pageTables   = array('i', [0])
committed_AS = array('i', [0])
vmallocUsed  = array('i', [0])

tr = TTree('tr', 'tr')
tr.Branch('memTotal', memTotal, 'memTotal/I')
tr.Branch('memFree', memFree, 'memFree/I')
tr.Branch('buffers', buffers, 'buffers/I')
tr.Branch('cached', cached, 'cached/I')
tr.Branch('swapCached', swapCached, 'swapCached/I')
tr.Branch('active', active, 'active/I')
tr.Branch('inactive', inactive, 'inactive/I')
tr.Branch('lowFree', lowFree, 'lowFree/I')
tr.Branch('swapFree', swapFree, 'swapFree/I')
tr.Branch('dirty', dirty, 'dirty/I')
tr.Branch('writeback', writeback, 'writeback/I')
tr.Branch('anonPages', anonPages, 'anonPages/I')
tr.Branch('mapped', mapped, 'mapped/I')
tr.Branch('slab', slab, 'slab/I')
tr.Branch('pageTables', pageTables, 'pageTables/I')
tr.Branch('committed_AS', committed_AS, 'committed_AS/I')
tr.Branch('vmallocUsed', vmallocUsed, 'vmallocUsed/I')

size = 0

for line in open(ifname, 'r'):
    sp = line.split()
    if len(sp) != 17:
        break

    memTotal[0]     = int(sp[0])
    memFree[0]      = int(sp[1])
    buffers[0]      = int(sp[2])
    cached[0]       = int(sp[3])
    swapCached[0]   = int(sp[4])
    active[0]       = int(sp[5])
    inactive[0]     = int(sp[6])
    lowFree[0]      = int(sp[7])
    swapFree[0]     = int(sp[8])
    dirty[0]        = int(sp[9])
    writeback[0]    = int(sp[10])
    anonPages[0]    = int(sp[11])
    mapped[0]       = int(sp[12])
    slab[0]         = int(sp[13])
    pageTables[0]   = int(sp[14])
    committed_AS[0] = int(sp[15])
    vmallocUsed[0]  = int(sp[16])
    tr.Fill()

f = TFile(ofname, 'RECREATE')
tr.Write()
f.Close()
