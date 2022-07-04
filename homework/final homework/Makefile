report:
	cd ./doc && xelatex report.tex
	cd ./doc && bibtex  report
	cd ./doc && xelatex report.tex
	cd ./doc && xelatex report.tex
	cd ./doc && rm report.aux
	cd ./doc && rm report.log
	cd ./doc && rm report.bbl
	cd ./doc && rm report.blg
	cd ./doc && rm report.run.xml
	mv ./doc/report.pdf .
	
slide :  
	cd ./doc && xelatex slide.tex
	cd ./doc && rm slide.aux
	cd ./doc && rm slide.log
	cd ./doc && rm slide.nav
	cd ./doc && rm slide.out
	cd ./doc && rm slide.snm
	cd ./doc && rm slide.toc
	cd ./doc && rm slide.run.xml
	cd ./doc && rm slide.bcf
	mv ./doc/slide.pdf .
