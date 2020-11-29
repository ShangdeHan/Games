package hw4;
/**
 * @author shangde Han
 */
import api.Cell;
import api.Position;
import api.Icon;

/**
 * This class is CornerPiece class, a subclass of AbstractPiece 
 * to create a CornerPiece
 */

/**
 * inherits from AbstractPiece class
 * @throws java.io.IllegalArgumentException
 * thorws IllegalArgumentException if givenicons' length does not equal to 3
 */
public class CornerPiece extends AbstractPiece{	
	public CornerPiece(Position givenPosition, Icon[] icons) throws IllegalArgumentException {
		super(givenPosition, icons);
		if(icons.length!=3) {
			throw new IllegalArgumentException("icons' length is not equal to 3");
		}
		Cell[] localCells = new Cell[icons.length];
		localCells[0] = new Cell(icons[0], new Position(0, 0));
		localCells[1] = new Cell(icons[1], new Position(1, 0));
		localCells[2] = new Cell(icons[2], new Position(1, 1));
	    setCells(localCells);
	}

	 /**
	   * Transforms this piece without altering its position
	   * according to the rules of the game to be implemented.  
	   * Typical operations would be rotation or reflection. 
	   * No bounds checking is done.
	   * abstracts this method, so in subclasses there are detailed method
	   * 
	   * this method performs a kind of rotation through four different states
	   */   
	public void transform() {
		int num = 0;
		Cell[] localCells2 = new Cell[getCells().length];
		for(int i = 0; i<localCells2.length;i++) {
			localCells2[i] = getCells()[i];
		}
		while(num < 3) {
		    int row = localCells2[num].getRow();
		    int col = localCells2[num].getCol();
		    if(row == 0 && col == 0) {
		    	row = 0;
		    	col = 1;
		    }else if(row == 0 && col == 1) {
		    	row = 1;
		    	col = 1;
		    }else if(row == 1 && col == 1) {
		    	row = 1;
		    	col = 0;
		    }else if(row == 1 && col == 0) {
		    	row = 0;
		    	col = 0;
		    }
			localCells2[num].setPosition(new Position (row, col));
		    num++;
		}
	    setCells(localCells2);
	}
}
