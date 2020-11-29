package hw4;
/**
 * @author shangde Han
 */
import api.Cell;
import api.Position;
import api.Icon;

/**
 * This class is IPiece class, a subclass of AbstractPiece 
 * to create a IPiece
 */

/**
 * inherits from AbstractPiece class
 * @throws java.io.IllegalArgumentException
 * thorws IllegalArgumentException if givenicons' length does not equal to 3
 */
public class IPiece extends AbstractPiece{
	public IPiece(Position givenPosition, Icon[] icons) throws IllegalArgumentException {
		super(givenPosition, icons);
		if(icons.length!=3) {
			throw new IllegalArgumentException("icons' length is not equal to 3");
		}
		Cell[] localCells = new Cell[icons.length];
		localCells[0] = new Cell(icons[0], givenPosition);
		localCells[1] = new Cell(icons[1], new Position(givenPosition.row()+1, givenPosition.col()));
		localCells[2] = new Cell(icons[2], new Position(givenPosition.row()+2, givenPosition.col()));
	    setCells(localCells);
	}
	
	 /**
	   * Transforms this piece without altering its position
	   * according to the rules of the game to be implemented.  
	   * Typical operations would be rotation or reflection. 
	   * No bounds checking is done.
	   * abstracts this method, so in subclasses there are detailed method
	   * 
	   * this method do nothing because IPiece cannot transform to other shapes.
	   */  
	public void transform() {
	}
}
