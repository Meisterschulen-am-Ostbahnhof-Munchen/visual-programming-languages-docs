# QUARTER_TO_STR_MEASURED

```{index} single: QUARTER_TO_STR_MEASURED
```

<img width="1521" height="186" alt="image" src="https://github.com/user-attachments/assets/90319dba-980a-464e-aa11-c9c9729af26a" />

* * * * * * * * * *
## 🎧 Podcast

* [QUARTER](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/QUARTER-e36741d)
* [Das Geheimnis des 2-Bit-Quarter: Effizienz im CAN-Bus für Nutzfahrzeuge](https://podcasters.spotify.com/pod/show/iec-61499-grundkurs-de/episodes/Das-Geheimnis-des-2-Bit-Quarter-Effizienz-im-CAN-Bus-fr-Nutzfahrzeuge-e3673bk)

## Einleitung
Der Funktionsblock `QUARTER_TO_STR_MEASURED` dient der Konvertierung eines 4-Zustands-Signals (kodiert in den unteren zwei Bits eines BYTE-Wertes) in einen menschenlesbaren Text-String (STRING). Er ist besonders für die Anzeige oder Protokollierung von Statusinformationen in Steuerungssystemen geeignet, wo diskrete Zustände wie "Eingeschaltet", "Ausgeschaltet", "Fehler" oder "Nicht verfügbar" in eine textuelle Form überführt werden müssen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
*   **REQ**: Startet die normale Ausführung des Funktionsblocks. Bei diesem Ereignis wird der Wert am Daten-Eingang `IB` ausgewertet und die entsprechende Konvertierung durchgeführt.

### **Ereignis-Ausgänge**
*   **CNF**: Signalisiert die Beendigung der Konvertierung und die Verfügbarkeit des Ergebnisses am Daten-Ausgang `STR`.

### **Daten-Eingänge**
*   **IB** (BYTE): Der Eingang für den zu konvertierenden 4-Zustands-Wert (Quad-State). Es werden nur die unteren zwei Bits (LSB) ausgewertet. Der Block erwartet spezifische, vordefinierte Konstantenwerte (z.B. `quarter::STATUS_ENABLED`). Der Initialwert ist `quarter::STATUS_DISABLED`.

### **Daten-Ausgänge**
*   **STR** (STRING): Der Ausgang, an dem der konvertierte Text-String bereitgestellt wird. Der Initialwert ist die Textkonstante für den Status "Disabled" (`quarter::STATUS_DISABLED_msg`).

### **Adapter**
Dieser Funktionsblock verfügt über keine Adapter-Schnittstellen.

## Funktionsweise
Der `QUARTER_TO_STR_MEASURED` ist ein Basic Function Block (BFB) mit einem internen Ausführungssteuerungsgraphen (ECC). Bei Eintreffen des `REQ`-Ereignisses wird der Wert am Eingang `IB` mit vordefinierten Konstanten aus der Bibliothek `logiBUS::utils::quarter::const::quarter` verglichen. Abhängig vom übereinstimmenden Wert verzweigt die Steuerung in einen von vier Zuständen (`SET`, `RESET`, `Error`, `none`). In jedem dieser Zustände wird ein spezifischer Algorithmus ausgeführt, der die entsprechende Textkonstante (z.B. `quarter::STATUS_ENABLED_msg`) dem Ausgang `STR` zuweist. Anschließend wechselt der Block in den Zustand `ok`, von dem aus das `CNF`-Ausgangsereignis ausgelöst wird, bevor der Block in seinen initialen Zustand `START` zurückkehrt und auf den nächsten `REQ` wartet.

## Technische Besonderheiten
*   **Typisierte Konstanten:** Der Block verwendet streng typisierte Konstanten für sowohl die Eingangswerte (`quarter::STATUS_...`) als auch die Ausgangsstrings (`quarter::STATUS_..._msg`). Dies erhöht die Typsicherheit und Wartbarkeit des Codes.
*   **Basic FB:** Die Implementierung als Basic FB mit ECC ermöglicht eine klare und nachvollziehbare Zustandslogik.
*   **Initialwerte:** Sowohl der Daten-Eingang `IB` als auch der Daten-Ausgang `STR` sind mit sinnvollen Initialwerten (deaktivierter Status) vorbesetzt.

## Zustandsübersicht
Der ECC des Funktionsblocks besteht aus sechs Zuständen:
1.  **START:** Der initiale Wartezustand. Bei `REQ` erfolgt eine Verzweigung basierend auf dem Wert von `IB`.
2.  **SET:** Wird bei `IB = quarter::STATUS_ENABLED` aktiviert. Führt den Algorithmus `SET` aus.
3.  **RESET:** Wird bei `IB = quarter::STATUS_DISABLED` aktiviert. Führt den Algorithmus `RESET` aus.
4.  **Error:** Wird bei `IB = quarter::STATUS_ERROR` aktiviert. Führt den Algorithmus `ERROR` aus.
5.  **none:** Wird bei `IB = quarter::STATUS_NOT_AVAILABLE` aktiviert. Führt den Algorithmus `NONE` aus.
6.  **ok:** Gemeinsamer Zustand, der nach jeder erfolgreichen Konvertierung durchlaufen wird. Löst das `CNF`-Ereignis aus und führt zurück zum `START`-Zustand.

## Anwendungsszenarien
*   **HMI/SCADA-Anbindung:** Konvertierung von internen Steuerungsstatuswerten in lesbare Texte für die Darstellung auf Bedienpanels oder in Visualisierungssystemen.
*   **Protokollierung und Diagnose:** Erzeugung von klartextbasierten Log-Einträgen für Fehler- oder Statusmeldungen, die einfacher zu analysieren sind als numerische Codes.
*   **Schnittstelle zu übergeordneten Systemen:** Aufbereitung von Statusinformationen für die Übertragung an MES- oder ERP-Systeme, die String-Daten erwarten.

## Vergleich mit ähnlichen Bausteinen
*   **`BYTE_TO_STRING`:** Ein genereller Konverter, der einen beliebigen BYTE-Wert in seine dezimale String-Repräsentation umwandelt. `QUARTER_TO_STR_MEASURED` ist spezialisierter und wandelt spezifische, semantisch bedeutungsvolle Werte in vordefinierte, aussagekräftige Texte um, nicht in Zahlenstrings.
*   **`E_SR` oder `E_RS` (FlipFlops):** Diese Blöcke repräsentieren binäre Zustände (SET/RESET) durch boolesche Signale. `QUARTER_TO_STR_MEASURED` erweitert dieses Konzept auf vier Zustände und bietet zusätzlich die textuelle Repräsentation.

## Fazit
Der `QUARTER_TO_STR_MEASURED` ist ein spezialisierter und robuster Funktionsblock zur semantischen Konvertierung von 4-Zustands-Signalen. Durch die Verwendung von Bibliothekskonstanten für Ein- und Ausgänge gewährleistet er eine hohe Codequalität und vereinfacht die Wartung. Er ist die ideale Wahl, wenn diskrete Statusinformationen aus der Steuerungsebene für Anzeige-, Protokollierungs- oder Schnittstellenzwecke in eine textuelle Form gebracht werden müssen.