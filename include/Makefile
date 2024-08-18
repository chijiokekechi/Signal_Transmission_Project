BYTE = byte
GRAY_CODE = gray_code
DECODER = decoder
SDR = sdr
LIB_TGTS = $(BYTE).o $(GRAY_CODE).o $(DECODER).o
CLEAN_TGTS = ../lib/lib$(SDR).so ../lib/$(BYTE).o ../lib/$(GRAY_CODE).o ../lib/$(DECODER).o

$(SDR):		$(LIB_TGTS)
		g++ -shared -o lib$(SDR).so $(LIB_TGTS)
		mv lib$(SDR).so $(LIB_TGTS) ../lib

$(BYTE).o:	$(BYTE).cpp $(BYTE).hpp
		g++ -c -fPIC $(BYTE).cpp
	
$(GRAY_CODE).o:	$(GRAY_CODE).cpp $(GRAY_CODE).hpp
		g++ -c -fPIC $(GRAY_CODE).cpp

$(DECODER).o:	$(DECODER).cpp $(DECODER).hpp
		g++ -c -fPIC $(DECODER).cpp

.PHONY: clean
clean:	$(CLEAN_TGTS)
	rm $(CLEAN_TGTS)
