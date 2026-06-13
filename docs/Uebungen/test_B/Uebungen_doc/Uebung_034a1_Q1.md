# Uebung_034a1_Q1: Numeric Value Input auf PWM Ausgang




[![NotebookLM](media/NotebookLM_logo.png)](https://notebooklm.google.com/notebook/a6872e59-1dfc-4132-a118-aff1bc7bc944)

## Übersicht

[cite_start]In dieser Übung wird ein numerischer Wert direkt vom ISOBUS-Terminal eingelesen, um die Tastrate eines PWM-Ausgangs (`Q1`) zu steuern[cite: 1].
Über das Objekt `InputNumber_PWM_Value` kann der Bediener am Bildschirm eine Zahl eingeben. Erst nach der Bestätigung mit "OK" wird das Ereignis `IND` gefeuert und der neue Wert an die PWM-Hardware übertragen. Dies ermöglicht die präzise manuelle Vorgabe von Leistungen (z.B. Lüfterdrehzahl oder Lampenhelligkeit) direkt über das Display.

![Uebung_034a1_Q1_network](./Uebung_034a1_Q1_network.svg)
