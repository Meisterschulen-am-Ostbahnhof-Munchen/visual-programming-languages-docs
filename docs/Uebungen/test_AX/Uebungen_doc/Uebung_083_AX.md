# Uebung_083_AX: Beispiel für AUDI_CTUD_UDINT (Adapter-basiert)




Dieser Artikel beschreibt die logiBUS®-Übung `Uebung_083_AX`. Sie ist die adapterbasierte Variante der Übung 083 und demonstriert einen Auf-/Abwärtszähler (`AUDI_CTUD_UDINT`) für vorzeichenlose 32-Bit-Ganzzahlen in einer AX-Umgebung.

----


## Ziel der Übung

Erlernen der adapterbasierten Steuerung eines Hochleistungs-Zählers und der Anzeige des Zählwerts auf einem ISOBUS-Terminal. Die Übung zeigt die Nutzung von AX-Adaptern für die Eingänge (`CU`, `CD`, `R`, `LD`) und den Zählwert (`CV`) sowie für die Ansteuerung der numerischen Anzeige.

-----

## Beschreibung und Komponenten

Die Subapplikation `Uebung_083_AX.SUB` nutzt folgende adapterbasierte Funktionsbausteine:

### Funktionsbausteine (FBs)

  * **`DigitalInput_CLK_I1` bis `I4`**: Eingangsbausteine vom Typ `logiBUS::io::DI::logiBUS_IXA`. Sie liefern über einen AX-Adapter ein Ereignis und ein Bool-Signal bei Tasterdruck.
  * **`AUDI_CTUD_UDINT`**: Der adapterbasierte Auf-/Abwärtszähler. Er erwartet Events an `CU`, `CD`, `R` und einen `AUDI`-Adapter an `PV` sowie gibt den Zählwert über den `CV`-Adapter aus.
  * **`DigitalOutput_Q1` & `Q2`**: Ausgangsbausteine vom Typ `logiBUS::io::DQ::logiBUS_QXA` für die Anzeige des Zählerstatus (`QU`, `QD`).
  * **`Q_NumericValue_AUDI`**: ISOBUS-Ausgangsbaustein für die numerische Anzeige am Terminal, empfängt den Wert über einen `AUDI`-Adapter.
  * **`AUDI_UDINT_TO_UDI`**: Konvertierungsbaustein, der einen `UDINT`-Literal (`UDINT#5`) in einen `AUDI`-Adapter umwandelt, um den `PV`-Eingang des Zählers zu versorgen.

-----

## Funktionsweise

1.  **Zählen**: `DigitalInput_CLK_I1.OUT` (Taster I1) triggert `AUDI_CTUD_UDINT.CU` (Zähler hoch). `DigitalInput_CLK_I2.OUT` (Taster I2) triggert `AUDI_CTUD_UDINT.CD` (Zähler runter).
2.  **Reset/Load**: `DigitalInput_CLK_I3.OUT` (Taster I3) triggert `AUDI_CTUD_UDINT.R` (Reset). `DigitalInput_CLK_I4.IND` triggert `AUDI_UDINT_TO_UDI.REQ`, der den Wert `UDINT#5` an `AUDI_CTUD_UDINT.PV` übergibt und damit den Zähler lädt.
3.  **Anzeige**: Der Zählerstatus `QU` und `QD` steuert `DigitalOutput_Q1.OUT` und `DigitalOutput_Q2.OUT`. Der aktuelle Zählerwert (`AUDI_CTUD_UDINT.CV`) wird an `Q_NumericValue_AUDI.u32NewValue` gesendet und am ISOBUS-Terminal angezeigt.

-----

## Hinweise zur Implementierung

*   **Eingangstypen**: Die `DigitalInput_CLK_I` Bausteine sind vom Typ `logiBUS_IE`, obwohl `logiBUS_IXA` die Adapter-Variante wäre. Deren `InputEvent`-Parameter sind in einem AX-Kontext redundant und könnten entfernt werden, wenn `logiBUS_IXA` verwendet wird.
*   **PV-Initialisierung**: Die direkte Zuweisung eines `PV`-Parameters (`UINT#5`) an `AUDI_CTUD_UDINT` ist nicht adaptergerecht. Die aktuelle Lösung über den Konverter `AUDI_UDINT_TO_UDI` ist funktional, aber etwas umständlich.