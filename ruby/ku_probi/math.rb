require_relative 'drawer'

class MathDrawer
	@drawer=Drawer.new "math.svg",300,300
	@drawer.start
	@drawer.cs

	def parabola a,b,c
		if a!=0
			x2=-(b/(2*a))
			y2=(x2*x2*a)+(x2*b)+c
			x1=x2-12.5
			y1=(x1*x1*a)+(x1*b)+c
			x3=x2+12.5
			y3=(x3*x3*a)+(x3*b)+c
			@drawer.path x1,y1,x2-x1,(y1-y2)*2,x3-x1,0
		else
			puts "That isn't a quadratic equation!"
		end
	end
	@drawer.finish
end

m=MathDrawer.new
m.parabola 1,-10,25
