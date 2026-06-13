# Uebung_009_AX: Ticker (AX-Adapter basiert)




Dieser Artikel beschreibt die logiBUS®-Übung `Uebung_009_AX`. Hier wird die Funktionsweise eines ereignisbasierten Zählers und einer numerischen Anzeige über AX-Adapter demonstriert, was zu einer kompakteren und übersichtlicheren Verdrahtung führt.

----


## Ziel der Übung

Erlernen der adapterbasierten Zählung (`AUDI_CTUD_UDINT`) und der Darstellung von Werten auf einem ISOBUS-Terminal (`Q_NumericValue_AUDI`). Der Fokus liegt auf der Nutzung von Adaptern zur Bündelung von Ereignis- und Datenfluss.

-----

## Beschreibung und Komponenten

Die Subapplikation `Uebung_009_AX.SUB` nutzt adapterbasierte Funktionsbausteine für den Taktgeber, den Zähler und die numerische Anzeige:

### Funktionsbausteine (FBs)

  * **`AE_CYCLE` & `AX_SR`**: Erzeugen einen permanenten Takt und steuern den Blinkerstatus über Adapter. Der `AX_SR` hat einen `AX`-Adapterausgang.
  * **`AX_SWITCH`**: Ein adapterbasierter Schalter, der den `AX`-Signalfluss basierend auf dem internen Blinker-Status umschaltet.
  * **`AX_PERMIT`**: Ein adapterbasiertes Ereignis-Gatter. Es lässt Ereignisse am Eingang `PERMIT.E1` nur dann zum Ausgang `EO` durch, wenn der Daten-Eingang `PERMIT.D1` auf `TRUE` steht.
  * **`AUDI_CTUD_UDINT`**: Ein adapterbasierter Vorwärts-/Rückwärtszähler. Er empfängt `CU`-Ereignisse und gibt den Zählerstand über einen `AUDI`-Adapter (`CV`) aus.
  * **`Q_NumericValue_AUDI`**: Ein ISOBUS-Ausgangsbaustein zur Anzeige einer Zahl auf dem Bildschirm. Er empfängt den Wert über einen `AUDI`-Adapter (`u32NewValue`).

-----

## Funktionsweise

1.  **Takt & Blinker**: `AE_CYCLE` erzeugt jede Sekunde ein `AE`-Ereignis. `AX_SR` toggelt seinen `AX`-Adapterausgang (`Q`) bei jedem Takt.
2.  **Konditionierung**: Der `AX_PERMIT` erhält das `AX`-Signal des `AX_SR`. Nur wenn der Blinker `TRUE` ist, wird ein Ereignis (`EO`) weitergeleitet.
3.  **Zählung**: Die durchgelassenen Events erreichen den `CU`-Eingang des `AUDI_CTUD_UDINT`. Der Zählerstand wird über den `CV`-Adapter ausgegeben.
4.  **Anzeige**: Bei jeder Änderung des Zählerstands (`AUDI_CTUD_UDINT.CO`) wird der Wert über den `u32NewValue`-Adapter an `Q_NumericValue_AUDI` gesendet.
5.  Auf dem ISOBUS-Terminal sieht der Nutzer eine Zahl, die stetig ansteigt.

-----

## Fazit

Diese Übung demonstriert die Vorteile einer konsequenten Adapter-basierten Entwicklung. Das Baustein-Netzwerk ist deutlich übersichtlicher, da Ereignis- und Datenflüsse in einer einzigen Verbindung gebündelt werden. Dies reduziert die Komplexität und Fehleranfälligkeit erheblich und erleichtert die Integration in verteilte Systeme.