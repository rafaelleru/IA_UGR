\ProvidesClass{application}[2014/03/04 v1.0 Simple application class]
\LoadClass{article}

\RequirePackage[T1]{fontenc}
\RequirePackage{lmodern}
\renewcommand*\familydefault{\sfdefault}
\RequirePackage{sfmath}
\RequirePackage{microtype}
\RequirePackage[utf8]{inputenc}

\usepackage{cfr-lm}

\RequirePackage{listings}
\lstset{language=java}

%\RequirePackage[ngerman]{babel}
%\RequirePackage[english]{babel}
\RequirePackage[spanish]{babel}
%\selectlanguage{english}
%\selectlanguage{german}
\RequirePackage[margin=2cm,a4paper]{geometry}

\RequirePackage{graphicx}
\graphicspath{{./}{../}{images/}}

%\RequirePackage[pdftex,
	%unicode=true,
	%breaklinks=true,
	%colorlinks=true,
	%linkcolor=black,
	%citecolor=black,
	%urlcolor=black]{hyperref}

\renewcommand{\baselinestretch}{1.1}
\setlength{\parindent}{0pt}
%\setlength{\parskip}{5pt}

\newcommand{\titleabstand}{\hspace{3cm}}
\newcommand{\RNum}[1]{\uppercase\expandafter{\romannumeral #1\relax}}

\renewcommand{\maketitle}{
\begin{titlepage}
	\thispagestyle{empty}
  \begin{minipage}[t]{1.0\textwidth}
	\includegraphics[scale=1.0]{images/ugr.jpg}
  \end{minipage}
  \begin{minipage}[t]{1.0\textwidth}
  \vspace{-1.7cm}
	\hfill
	\includegraphics[scale=0.85]{images/etsiit.jpg}
  \end{minipage}

 \begin{minipage}{\textwidth}
  \ \\
  \vspace{0.5cm}

  \begin{minipage}[t]{1.0\textwidth}
  	\begin{flushright}
	\Huge{Practica 3:\\ Busqueda en juegos con informacion perfecta}\\
	\Large ss 2016
  	\end{flushright}
    \end{minipage}
  %\hspace{1.8cm}
\end{minipage}

\hspace{3cm}
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak
\linebreak

\Large
\begin{flushright}
Rafael Leyva\\
Grupo A.1\\
\end{flushright}

\vspace{-0.9cm}
\begin{flushleft}
\href{mailto:rafaelleru95103@correo.ugr.es}{rafaelleru95103@correo.ugr.es}
\end{flushleft}

\end{titlepage}
}
