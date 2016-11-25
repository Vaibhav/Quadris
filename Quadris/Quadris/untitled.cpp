void Board::notify(Subject &whoNotified) {
	Info cellInfo = whoNotified.getInfo();
	theBoard[cellInfo.row][cellInfo.col] = cellInfo.displayChar;
}