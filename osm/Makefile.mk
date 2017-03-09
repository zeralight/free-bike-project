all:
	@qmake downloader.pro
	@make
	@qmake xml.pro
	@make
	@qmake paths_calculations.pro
	@make
	@qmake tulip_graph_builder.pro
	@make
.PHONY: clean
clean:
	@rm -f *.o downloader xml paths_calculations tulip_graph_builder
