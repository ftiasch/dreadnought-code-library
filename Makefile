all:
	xelatex -shell-escape main.tex
	xelatex -shell-escape main.tex
	open main.pdf
clean:
	rm main.log main.pdf main.toc main.aux
	rm -rf _minted-main
