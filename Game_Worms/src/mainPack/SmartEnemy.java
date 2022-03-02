package mainPack;

import java.awt.Color;
import java.awt.Graphics;
//import java.awt.Graphics2D;
import java.awt.Rectangle;

public class SmartEnemy extends GameObject {

	private Handler handler;
	private GameObject player;
	
	public SmartEnemy(int x, int y, ID id, Handler handler) {
		super(x, y, id);
		this.handler = handler;
		
		for(int i = 0; i < handler.objectList.size(); i++){
			if(handler.objectList.get(i).getID() == ID.Player) 
				player = handler.objectList.get(i); //getting the player from the list
		}

	}

	public void tick() {
		x += velX;
		y += velY;
		
		float diffX = x - player.getX() - 8; //distance to the centre of the Player
		float diffY = y - player.getY() - 8;
		float distance = (float) Math.sqrt(Math.pow(diffX, 2) + Math.pow(diffY, 2));
		
		//Making the Enemy move in the direction of the player
		velX = ((-1f / distance) * diffX)*2f;
		velY = ((-1f / distance) * diffY)*2f;
		
		if (y <= 0 || y >= Game.HEIGHT - 64) velY *= -1;
		if (x <= 0 || x >= Game.WIDTH - 32) velX *= -1;
		
		handler.addObject(new Trail(x, y, 16, 16, 0.06f, ID.Trail, Color.yellow, handler));
		
	}

	public void render(Graphics g) {
		
		//Graphics2D g2d = (Graphics2D) g;
		
		g.setColor(Color.yellow);
		g.fillRect((int)x,(int) y, 16, 16);
		
	}
	
	public Rectangle getBounds(){
		return new Rectangle((int)x, (int)y, 16, 16);
	}

}
