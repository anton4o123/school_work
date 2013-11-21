require_relative 'drawer'
require_relative 'vertex'

d=Drawer.new "graph.svg",300,300
d.start

v=Vertex.new "78.90.214.6"
v.draw d,0,0

v2=Vertex.new "78.90.214.48"
v2.draw d,100,100

d.finish
