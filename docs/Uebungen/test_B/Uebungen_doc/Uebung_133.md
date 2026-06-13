# Uebung_133: Übung zu ISOBUS Request Message Cyclic




[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)

Dieser Artikel beschreibt die logiBUS®-Übung `Uebung_133`.

----


## Übersicht

[cite_start]Kombination aus Abfrage und zyklischer Überwachung unter Verwendung von `AlPgnRxNew8Bcylc_REQ`[cite: 1].
Dieser Baustein sendet in festen Abständen eigenständig Anfragen an den Partner und überwacht gleichzeitig das Eintreffen der Antworten innerhalb der Kontrollzeit. Dies ist die sicherste Form der Kommunikation für Daten, die nicht automatisch vom Partner gesendet werden, aber dennoch permanent aktuell sein müssen.

![Uebung_133_network](./Uebung_133_network.svg)
