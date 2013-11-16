require 'rexml/document'

def line(parent,x1,x2,y1,y2)
	l=parent.add_element "line"
	l.attributes["x1"]=x1
	l.attributes["x2"]=x2
	l.attributes["y1"]=y1
	l.attributes["y2"]=y2
	l.attributes["stroke-width"]="2"
	l.attributes["stroke"]="black"
end

def circle(parent,x,y,r)
	c=parent.add_element "circle"
	c.attributes["cx"]=x
	c.attributes["cy"]=y
	c.attributes["r"]=r
	c.attributes["stroke"]="black"
	c.attributes["fill"]="white"
	c.attributes["stroke-width"]="2"
end

doc=REXML::Document.new
el_svg=doc.add_element "svg"
el_svg.attributes["version"]="1.1"
el_svg.attributes["xmlns"]="http://www.w3.org/2000/svg"

circle(el_svg,200,200,100)
circle(el_svg,200,410,100)

line(el_svg,195,195,300,310)
line(el_svg,205,205,300,310)

File.open("clock.svg","w") do |svg|
	svg.write(doc.to_s)
end
