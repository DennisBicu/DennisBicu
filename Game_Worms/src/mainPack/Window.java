package mainPack;

import java.awt.Canvas;
import java.awt.Dimension;

import javax.swing.JFrame;

public class Window extends Canvas{

	private static final long serialVersionUID = -8947125168908818501L;
	
	public Window (int width, int height, String title, Game game){
		
		JFrame frame = new JFrame(title);
		frame.setPreferredSize(new Dimension (width, height));
		frame.setMaximumSize(new Dimension (width, height));
		frame.setMinimumSize(new Dimension (width, height));
		
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setResizable(false); //frame is not resizable
		frame.setLocationRelativeTo(null); //window to start in the middle of the screen
		frame.add(game);
		frame.setVisible(true);
		game.start();
		
	}

}
