require 'rexml/document'

def circle(parent,x,y,r,red=0,green=0,blue=255)
	c=parent.add_element "circle"
	c.attributes["cx"]=x
	c.attributes["cy"]=y
	c.attributes["r"]=r
	c.attributes["fill"]="rgb(#{red},#{green},#{blue})"
	c.attributes["stroke"]="black"
	c.attributes["stroke-width"]="2"
end

def rect(parent,w,h)
	r=parent.add_element "rect"
	r.attributes["width"]=w
	r.attributes["height"]=h
	r.attributes["stroke"]="black"
	r.attributes["stroke-width"]="2"
	r.attributes["fill"]="blue"
end

doc=REXML::Document.new
el_svg=doc.add_element "svg"
el_svg.attributes["version"]="1.1"
el_svg.attributes["xmlns"]="http://www.w3.org/2000/svg"

20.downto(1) do |i|
	circle(el_svg,100+i*10,100+i*10,i*10,blue=i*10)
end
rect(el_svg,200,200)

File.open("result.svg","w") do |svg|
	svg.write(doc.to_s)
end
