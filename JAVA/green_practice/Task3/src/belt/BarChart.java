package belt;

public class BarChart extends Chart implements AntonGeorgiev3 {

	public BarChart(int value) {
		this.value1=value*3;
		this.value2=value*5;
	}

	public void anton() {
		value2+=value1*2;
	}
}