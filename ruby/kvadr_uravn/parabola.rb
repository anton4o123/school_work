require 'rexml/document'

class Drawer
	attr_writer :file_name
	attr_reader :file_name
	attr_accessor :x
	attr_accessor :y

	def initialize file_name="result.svg",x,y
		self.file_name=file_name
		self.x=x
		self.y=y
	end

	def line x1,y1,x2,y2
		l=@el_svg.add_element "line"
		l.attributes["x1"]=self.x+x1
		l.attributes["x2"]=self.x+x2
		l.attributes["y1"]=self.y-y1
		l.attributes["y2"]=self.y-y2
		l.attributes["stroke"]="black"
		l.attributes["stroke-width"]="2"
	end

	def start
		@doc=REXML::Document.new
		@el_svg=@doc.add_element "svg"
		@el_svg.attributes["version"]="1.1"
		@el_svg.attributes["xmlns"]="http://www.w3.org/2000/svg"
	end

	def finish
		File.open(self.file_name,"w") do |svg|
			svg.write(@doc.to_s)
		end
	end

	def cs
		line -150,0,150,0
		line 0,-150,0,150
	end
end

drawer=Drawer.new "result.svg",300,300
drawer.start
drawer.cs
drawer.finish
