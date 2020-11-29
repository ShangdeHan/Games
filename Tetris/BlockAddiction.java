package hw4;
/**
 * @author shangde Han
 */
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.Random;
import api.AbstractGame;
import api.Generator;
import api.Icon;
import api.Position;

/**
 * A subclass of AbstractGame for Tetris-like falling shape games. 
 */
public class BlockAddiction extends AbstractGame {
	/**
	 * Constructs a new AbstracticonGame
	 * The height, width, and generator are just passed to the superclass constructor.
	 * @param height
	 * Height of the game grid.
	 * @param width
	 * Width of the game grid.
	 * @param gen
	 * Generator for new pieces. See the documentation for BasicGenerator
	 * as an example
	 */
	public BlockAddiction(int height, int width, Generator gen) {
		super(height, width, gen);
	}
	
	/**
	 * Constructs a new AbstracticonGame
	 * The height, width, and generator are passed to the superclass constructor,
	 * and a new parameter of preFillRows
	 * @param height
	 * Height of the game grid.
	 * @param width
	 * Width of the game grid.
	 * @param gen
	 * Generator for new pieces. See the documentation for BasicGenerator
	 * as an example.
	 * @param preFillRows
	 * If preFillRows is greater than zero, initialize the bottom preFillRows rows
	 * in a checkerboard pattern, using random icons obtained from the generator.
	 * The checkerboard pattern place an icon at (row, col) in the grid if both 
	 * row and col are even, or if both row and col are odd.
	 */
	public BlockAddiction(int height, int width, Generator gen, int preFillRows) {
		super(height, width, gen);
		if(preFillRows>0) {
			Icon icon = new BasicGenerator(new Random()).randomIcon();
			for(int row = 0; row<preFillRows;row++){
				for(int col = 0; col<width; col++) {
					if((row%2==0&&col%2==0)||((row%2!=0&&col%2!=0))) {
						setBlock(height-(preFillRows-row), col, icon);
					}
				}
			}
		}
	}

	/**
	 * A collapsible set is defined to be any set of three or
	 * more adjacent icons with the same color.
	 * Returns a list of locations for all cells that form part of
	 * a collapsible set.
	 * @return 
	 * list of locations for positions to be collapsed
	 */
	public List<Position> determinePositionsToCollapse() {
	    List<Position> positions = new ArrayList<>();
	    for(int i = 0; i<TotalPositionsToCollapse().size();i++) {
	    	
	    	positions.add(TotalPositionsToCollapse().get(i));
	    }
	    //remove duplicated positioins
	    removeDuplicatePositions(positions);
	    // sort positions
	    Collections.sort(positions);
	    return positions;
	}
	
	/**
	 * filter positions, which position adjancent positions have more than 2, 
	 * and set these cells in a Position arraylist
	 * @return
	 * total positions, any set of three or
	 * more adjacent icons with the same color
	 */
	private ArrayList<Position> TotalPositionsToCollapse() {
		ArrayList<Position> position3 = new ArrayList<Position>();
		for (int row = 0; row < getHeight(); row++) {
			for (int col = 0; col < getWidth(); col++) {
				ArrayList<Position> arr = CollectPositions(row, col);
				// determain whether this cell's round has more than 2 same icon
				if(arr.size()>2) {
					for(int i = 0; i<arr.size();i++) {
						
						position3.add(arr.get(i));
					}
				}
			}
		}
		return position3;
	}
	
	/**
	 * Collects a cell's adjancent positions in the grid
	 * if the position has adjancent same icon, collect them
	 * in a position arraylist
	 * @param row
	 * the row of this cell
	 * @param col
	 * the column of this cell
	 * @return
	 * an arraylist of this cell's round Positions, if this cell has icon
	 */
	private ArrayList<Position> CollectPositions(int row, int col) {
		ArrayList<Position> position2 = new ArrayList<Position>();
		// if this cell do not have icon, move on
		if(getIcon(row, col)!=null) {
			position2.add(new Position(row, col));
			if(row-1>=0) {
				if(getIcon(row, col).equals(getIcon(row-1, col))) {
					position2.add(new Position(row-1, col));
				}
			}if(row+1<getHeight()) {
				if(getIcon(row, col).equals(getIcon(row+1, col))) {
					position2.add(new Position(row+1, col));
				}
			}if(col-1>=0) {
				if(getIcon(row, col).equals(getIcon(row, col-1))) {
					position2.add(new Position(row, col-1));
				}
			}if(col+1<getWidth()) {
				if(getIcon(row, col).equals(getIcon(row, col+1))) {
					position2.add(new Position(row, col+1));
				}
			}	
		}
		return position2;
	}
	
	/**
	 * remove duplicate positions in the all positions
	 * @param positions
	 * an arraylist of positions
	 */
	private void removeDuplicatePositions(List<Position> positions) {
		for(int j = 0; j<positions.size();j++) {
			for(int m = j+1; m<positions.size();m++) {
				if(positions.get(j).equals(positions.get(m))) {
					positions.remove(m);
				}
			}
		}
	}
}