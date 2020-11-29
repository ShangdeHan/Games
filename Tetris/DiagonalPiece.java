package hw4;
/**
 * @author shangde Han
 */
import api.Cell;
import api.Position;
import api.Icon;

/**
 * This class is DiagonalPiece class, a subclass of AbstractPiece 
 * to create a DiagonalPiece
 */

/**
 * inherits from AbstractPiece class
 * @throws java.io.IllegalArgumentException
 * thorws IllegalArgumentException if givenicons' length does not equal to 2
 */
public class DiagonalPiece extends AbstractPiece{
	public DiagonalPiece(Position givenPosition, Icon[] icons) throws IllegalArgumentException {
		super(givenPosition, icons);
		if(icons.length!=2) {
			throw new IllegalArgumentException("icons' length is not equal to 2");
		}
		Cell[] localCells = new Cell[icons.length];
		localCells[0] = new Cell(icons[0], new Position(0, 0));
		localCells[1] = new Cell(icons[1], new Position(1, 1));
	    setCells(localCells);
	}
	
	 /**
	   * Transforms this piece without altering its position
	   * according to the rules of the game to be implemented.  
	   * Typical operations would be rotation or reflection. 
	   * No bounds checking is done.
	   * abstracts this method, so in subclasses there are detailed method
	   * 
	   * this method flips the cells across the vertical centerline,
	   */   
	public void transform() {
		Cell[] localCells2 = new Cell[getCells().length];
		for(int i = 0; i<localCells2.length;i++) {
			localCells2[i] = getCells()[i];
		}
		if(localCells2[0].getCol()==0) {
			localCells2[0].setPosition(new Position (0, 1));
			localCells2[1].setPosition(new Position (1, 0));

		}else if(localCells2[0].getCol()==1) {
			localCells2[0].setPosition(new Position (0, 0));
			localCells2[1].setPosition(new Position (1, 1));
			}
		setCells(localCells2);
	}
}
