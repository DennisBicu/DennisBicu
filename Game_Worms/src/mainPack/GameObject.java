package mainPack;

import java.awt.Graphics;
import java.awt.Rectangle;

public abstract class GameObject { //e.g.: a Player, an Enemy, Coins, etc. (any object in the game)
	
	protected float x, y; //coordinates of the object
	protected ID id; //identifying the object with the enum
	protected float velX, velY; //speed on the X axis and speed on the Y axis;
	
	public GameObject(float x, float y, ID id){
		this.x = x;
		this.y = y;
		this.id = id;
	}
	
	public abstract void tick();
	public abstract void render(Graphics g);
	public abstract Rectangle getBounds();
	
	
	//GETTERS AND SETTERS
	public void setX(int x){
		this.x = x;
	}
	
	public float getX(){
		return x;
	}
	
	public void setY(int y){
		this.y = y;
	}
	
	public float getY(){
		return y; 
	}
	
	public void setID(ID id){
		this.id = id;
	}
	
	public ID getID(){
		return id;
	}
	
	public void setVelX(int velX){
		this.velX = velX;
	}
	
	public float getVelX(){
		return velX;
	}
	public void setVelY(int velY){
		this.velY = velY;
	}
	
	public float getVelY(){
		return velY;
	}
}
