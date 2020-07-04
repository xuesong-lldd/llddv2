#!/usr/bin/env python
from ROOT import TTree, TFile, gROOT, gStyle, TCanvas, TGraph, TLegend
from array import array

f = TFile('mleak_chk.root')
tr = f.Get('tr')

gROOT.SetStyle('Plain')

c = TCanvas('c', 'c', 640, 480)
c.SetTopMargin(0.05)
c.SetRightMargin(0.05)

gStyle.SetGridStyle(1)
gStyle.SetGridColor(16)
c.SetGrid()
h = c.DrawFrame(0, 0, 8000, 1200)
N = tr.GetEntries()

tr.Draw('committed_AS/1000:Entry$', '', 'goff')
g1 = TGraph(tr.GetSelectedRows(), tr.GetV2(), tr.GetV1())
g1.SetLineWidth(2)
g1.Draw('')

tr.Draw('memFree/1000:Entry$', '', 'goff')
g2 = TGraph(tr.GetSelectedRows(), tr.GetV2(), tr.GetV1())
g2.SetLineWidth(2)
g2.SetLineStyle(2)
g2.Draw('')

tr.Draw('swapFree/1000:Entry$', '', 'goff')
g3 = TGraph(tr.GetSelectedRows(), tr.GetV2(), tr.GetV1())
g3.SetLineStyle(4)
g3.SetLineWidth(3)
g3.Draw('')

tr.Draw('anonPages/1000:Entry$', '', 'goff')
g4 = TGraph(tr.GetSelectedRows(), tr.GetV2(), tr.GetV1())
g4.SetLineWidth(1)
g4.Draw('')

tr.Draw('cached/1000:Entry$', '', 'goff')
g5 = TGraph(tr.GetSelectedRows(), tr.GetV2(), tr.GetV1())
g5.SetLineStyle(3)
g5.SetLineWidth(1)
g5.Draw('')

# Axis
h.SetXTitle('Time')
h.SetYTitle('(MB)')
h.SetTitleOffset(1.2, "Y")

# Legend
leg = TLegend(0.6, 0.17, 0.9, 0.41)
leg.SetFillColor(10)
leg.AddEntry(g3, 'SwapFree', 'l')
leg.AddEntry(g2, 'MemFree', 'l')
leg.AddEntry(g5, 'Cached', 'l')
leg.AddEntry(g1, 'Committed_AS', 'l')
leg.AddEntry(g4, 'AnonPages', 'l')
leg.Draw()

# Print out
c.Print('p1.eps')
