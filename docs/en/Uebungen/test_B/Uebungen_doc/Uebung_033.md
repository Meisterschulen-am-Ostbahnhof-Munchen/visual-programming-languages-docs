# Exercise_033: LED Strip Flashing LED

[![NotebookLM](media/NotebookLM_logo.png)(https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)
This article describes the logiBUS® exercise `Uebung_033`.
----
## Overview

[cite_start]This is the modular version of exercise 032[cite: 1]. The logic for a colored LED channel has been moved to a typed sub-application `Uebung_033_sub`. The main program instantiates this type four times and assigns it the pushbuttons `I1` to `I4` as well as the target colors. This again demonstrates the advantages of reusability with complex hardware components such as LED controllers.