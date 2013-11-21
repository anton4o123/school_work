require_relative 'drawer'

class Vertex
	attr_accessor :name

	def initialize name
		self.name=name
	end

	def draw drawer,x,y
		drawer.circle x,y,5
		drawer.text self.name,x+10,y+10
	end
end
