# Exercise_012a: Numeric Value Input and Storage (NVS) with Sub-Application

[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)
This article describes the logiBUS® exercise `Uebung_012a`. Here, the persistent storage from Exercise 012 is encapsulated in a reusable sub-application.
----
## Overview

[cite_start]The sub-application `Uebung_012a.SUB` uses the sub-app type `Uebung_012a_sub` to provide the storage logic modularly[cite: 1]. The block `CbVtStatus` remains at the top level to update the entire page as needed.

[cite_start]
### Typed Sub-Application: `Uebung_012a_sub`

[cite_start]This module bundles the input via `NumericValue_ID`, the conversion, NVS access, and the display feedback.[cite: 2] It provides interfaces for the memory key (`KEY`) and the object ID (`u16ObjId`).

This makes it possible to integrate many different settings (e.g., pressure, flow rate, time) into the program very quickly and clearly, without having to redraw the complex network from Exercise 012 each time.
