require 'rexml/document'

def line(parent,x1,x2,y1,y2,red=0,green=0,blue=0)
	l=parent.add_element "line"
	l.attributes["x1"]=x1
	l.attributes["x2"]=x2
	l.attributes["y1"]=y1
	l.attributes["y2"]=y2
	l.attributes["stroke-width"]="2"
	l.attributes["stroke"]="rgb(#{red},#{green},#{blue})"
end

doc=REXML::Document.new
el_svg=doc.add_element "svg"
el_svg.attributes["version"]="1.1"
el_svg.attributes["xmlns"]="http://www.w3.org/2000/svg"

line(el_svg,100,100,100,200,0,0,255)
line(el_svg,100,500,200,200,red=255)
line(el_svg,100,500,100,200,0,255)

File.open("triangle.svg","w") do |svg|
	svg.write(doc.to_s)
end
