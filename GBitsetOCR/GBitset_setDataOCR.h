void GBitsetOCR::setData(commandData *inputData_,
						 letterBase *aliKali_,
						 vector<stringOCR>&strArray_,
					     vector<stringOCR>&correctionTable, //vector of all uncertan letters from OCR text for draw in correction table
						 GLogicProcessor *logicProcessor,   //dictionary controll object
 						 int iLeft_,
						 int iTop_,
						 int border,
						 int mode
						 ) {   //main point for glyphOCR Object. Order of all Letter OCR function

	inputData=inputData_;
	aliKali=aliKali_;
	strArray=&strArray_;
		iLeft=iLeft_;
		iTop=iTop_;
		//bitsetBorder=border;   //size of border in string detector //NEED REWRITE
	
	//_DC("ALL vector COUNT "<<vectorBase[0][0].allVectorCount<<END);
    //_DC("ALL letter COUNT "<<letterBase[0].base.size()<<END);
	//DP("ALL string COUNT "<<strArray[0].size()<<END);
	textOCR(correctionTable, logicProcessor, mode);


}//___________________________________________________________________________________________________
