package hw4;
/**
 * @author shangde Han
 */
import api.Cell;
import api.Position;
import api.Icon;

/**
 * This class is LPiece class, a subclass of AbstractPiece 
 * to create a LPiece
 */

/**
 * inherits from AbstractPiece class
 * @throws java.io.IllegalArgumentException
 * thorws IllegalArgumentException if givenicons' length does not equal to 4
 */
public class LPiece extends AbstractPiece{
	public LPiece(Position givenPosition, Icon[] icons) {
		super(givenPosition, icons);
		if(icons.length!=4) {
			throw new IllegalArgumentException("icons' length is not equal to 4");
		}
		Cell[] localCells = new Cell[icons.length];
		localCells[0] = new Cell(icons[0], new Position(0, 0));
		localCells[1] = new Cell(icons[1], new Position(0, 1));
		localCells[2] = new Cell(icons[2], new Position(1, 1));
		localCells[3] = new Cell(icons[3], new Position(2, 1));
	    setCells(localCells);
	}
	
	 /**
	   * Transforms this piece without altering its position
	   * according to the rules of the game to be implemented.  
	   * Typical operations would be rotation or reflection. 
	   * No bounds checking is done.
	   * abstracts this method, so in subclasses there are detailed method
	   * 
	   * this method flips it across its vertical centerline
	   */   
	public void transform() {
		Cell[] localCells2 = new Cell[getCells().length];
		for(int i = 0; i<localCells2.length;i++) {
			localCells2[i] = getCells()[i];
		}
		if(localCells2[0].getCol() == 0) {
			localCells2[0].setPosition(new Position (0, 2));
		}else {
			localCells2[0].setPosition(new Position (0, 0));
		}
		setCells(localCells2);
	}
}
