package hw4;
/**
 * @author shangde Han
 */
import api.Cell;
import api.Icon;
import api.Piece;
import api.Position;

/**
 * This class is a AbstractPiece, create a supper class for pieces in games,
 * includinig some pieces' fuctions, like transform and cycle.
 */

/**
 * Partial implementation of the Piece interface for AbstractPiece.
 */
public abstract class AbstractPiece implements Piece {
	/**
	 * a position
	 */
	private Position position;
	/**
	 * an array of cells
	 */
	private Cell[] cells;
	
	/**
	 * Construct a AbstractPiece construcor, given as a position and an array of icons
	 * @param givenPosition
	 * the givenPosition to determain how many rows and cols in a grid
	 * @param icons
	 * to determain how many icons in the game and save these icons in an array
	 */
	protected AbstractPiece(Position givenPosition, Icon[] icons){
		position = givenPosition;	
		cells = new Cell[icons.length];
	}
	
	/**
	 * get position from the instance variable
	 * @return
	 * returns the position of this piece(upper-left corner of its bounding box)
	 */
	@Override
	public Position getPosition() {
		return position;
	}
	
	/**
	 * get an array of cells from instance variable cells
	 * @return
	 * returns a deep copy of the Cell object in this piece. The cell positions
	 * are relative to the upper-left corner of its bounding box
	 */
	@Override
	public Cell[] getCells() {
		Cell[] copy = new Cell[cells.length];
		for(int i = 0; i<cells.length;i++) {
			copy[i] = new Cell(cells[i]);
		}
		return copy;
	}
	
	/**
	 * this method that enables the caller to obtain the actual positions,
	 * within the grid, of the icons in the piece.
	 * @return
	 * returns a new array of Cell objects representing the icons in this piece with their absolute positions
	 * (relative positions plus positions of bounding box)
	 */
	@Override
	public Cell[] getCellsAbsolute() {
	    Cell[] ret = new Cell[cells.length];
	    for(int i = 0; i<cells.length;i++) {
		    int row = cells[i].getRow() + position.row();
		    int col = cells[i].getCol() + position.col();
		    Icon b = cells[i].getIcon();
		    ret[i] = new Cell(b, new Position(row, col));
	    }
		return ret;
	}
	
	/**
	 * Sets the cells in this piece, making a deep copy of the given array
	 */
	@Override
	public void setCells(Cell[] givenCells) {
		cells = new Cell[givenCells.length];
		for(int i = 0; i<cells.length;i++) {
			cells[i] = new Cell(givenCells[i]);
		}
	}
	
	 /**
	   * Shifts the position of this piece down (increasing the row) 
	   * by one.  No bounds checking is done.
	   */
	@Override
	public void shiftDown() {
	    position = new Position(position.row() + 1, position.col());
	}
	
	 /**
	   * Shifts the position of this piece left (decreasing the column) 
	   * by one.  No bounds checking is done.
	   */
	@Override
	public void shiftLeft() {
	    position = new Position(position.row(), position.col()-1);
	}
	
	 /**
	   * Shifts the position of this piece right (increasing the column) 
	   * by one.  No bounds checking is done. 
	   */  
	@Override
	public void shiftRight() {
	    position = new Position(position.row(), position.col()+1);
	}
	
	 /**
	   * Transforms this piece without altering its position
	   * according to the rules of the game to be implemented.  
	   * Typical operations would be rotation or reflection. 
	   * No bounds checking is done.
	   * abstracts this method, so in subclasses there are detailed method
	   */   
	@Override
	public abstract void transform(); 

	/**
	   * Cycles the icons within the cells of this piece.  Each 
	   * icon is shifted forward to the next cell (in the original ordering
	   * of the cells).  The last icon wraps around to the first cell.  
	   */
	@Override
	public void cycle() {
		int num = 0;
		Cell[] copy = getCells();
		while(num<cells.length) {
		    Icon icon = copy[num].getIcon();
		    if(num < cells.length-1) {
		    	cells[num+1].setIcon(icon);
		    }else if(num == (cells.length-1)) {
		    	cells[0].setIcon(icon);
		    }
		    num++;
		}
	}
	
	/**
	   * Returns a deep copy of this object having the correct runtime type.
	   * @return 
	   *   a deep copy of this object
	   */
	@Override
	public Piece clone() {
		 try
		    {
		      // call the Object clone() method to create a shallow copy
			 AbstractPiece s = (AbstractPiece) super.clone();

		      // then make it into a deep copy (note there is no need to copy the position,
		      // since Position is immutable, but we have to deep-copy the cell array
		      // by making new Cell objects      
		      s.cells = new Cell[cells.length];
		      for (int i = 0; i < cells.length; ++i)
		      {
		        s.cells[i] = new Cell(cells[i]);
		      }
		      return s;
		    }
		    catch (CloneNotSupportedException e)
		    {
		      // can't happen, since we know the superclass is cloneable
		      return null;
		    }    
	  }
}

