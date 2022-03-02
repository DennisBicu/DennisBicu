package mainPack;

import java.awt.AlphaComposite;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;

public class Trail extends GameObject{

	private float alpha = 1;
	private Handler handler;
	private Color color;
	
	private int width, height;
	private float life;
	
	//life = 0.001 -> 0.1
	
	public Trail(float x, float y, int width, int height, float life, ID id, Color color, Handler handler) {
		super(x, y, id);
		this.handler = handler;
		this.color = color;
		this.width = width;
		this.height = height;
		this.life = life;

	}

	public void tick() {
		if (alpha > life){
			alpha = alpha - (life - 0.0001f);
		} else handler.removeObject(this);
		
	}

	public void render(Graphics g) {
		// TODO Auto-generated method stub
		Graphics2D g2d = (Graphics2D) g;
		g2d.setComposite(makeTransparent(this.alpha));
		
		g.setColor(color);
		g.fillRect((int)x, (int)y, width, height);
		
		g2d.setComposite(makeTransparent(1));
		
	}
	
	//In order to receive transparent/faded colors
	public AlphaComposite makeTransparent (float alpha){
		int type = AlphaComposite.SRC_OVER;
		return AlphaComposite.getInstance(type, alpha);
	}

	public Rectangle getBounds() {
		// TODO Auto-generated method stub
		return null;
	}
	
}
