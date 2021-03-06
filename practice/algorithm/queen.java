/**
 * 单数组方式实现八皇后问题
 * Java语言实现
 * @author dainslef
 */

public class queen {

	class Queen
	{
		private final int QUEEN_SIZE = 8;
		private int count = 0;
		private int[] chessBoard = new int[QUEEN_SIZE];

		public int getCount() {
			return count;
		}

		public void queen(int row) {
			if (row == QUEEN_SIZE) {
				count++;
				System.out.println("\n找到了第" + count + "种方法：");
				show();
			} else {
				for (int i = 0; i < QUEEN_SIZE; i++)
					if (find(row, i))
					{
						chessBoard[row] = i;
						queen(row + 1);
					}
			}
		}

		private boolean find(int row, int line) {
			for (int i = 0; i < row; i++)
				if (line == chessBoard[i] || Math.abs(chessBoard[i] - line) == Math.abs(i - row))
					return false;
			return true;
		}

		private void show() {
			for (int i = 0; i < QUEEN_SIZE; i++)
				for (int p = 0; p < QUEEN_SIZE; p++) {
					System.out.print(p == chessBoard[i] ? "X  " : "_  ");
					if (p == QUEEN_SIZE - 1) System.out.println();
				}
		}
	}

	public static void main(String[] args) {
		Queen q = new Queen();
		q.queen(0);
		System.out.println("\n共找到了" + q.getCount() + "种解法。");
	}

}
