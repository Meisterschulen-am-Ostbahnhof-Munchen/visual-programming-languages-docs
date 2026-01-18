# ST08X_TO_BOOLS

```{index} single: ST08X_TO_BOOLS
```

<img width="1020" height="423" alt="image" src="https://github.com/user-attachments/assets/4fc3f598-930f-475b-b552-aefad4b5bb28" />

* * * * * * * * * *
## Einleitung
Dieser Funktionsblock dient dazu, acht individuelle BOOL-Werte aus einer einzelnen Eingangsstruktur vom Typ `ST08X` zu extrahieren. Er ermöglicht die einfache Zerlegung einer gebündelten 8-BOOL-Struktur in ihre einzelnen Komponenten.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
*   **REQ**: Ein Ereignis an diesem Eingang fordert die Konvertierung an. Es signalisiert dem Funktionsblock, die Daten vom Eingang `IN` zu verarbeiten.

### **Ereignis-Ausgänge**
*   **CNF**: Dieses Ereignis wird ausgegeben, sobald die Konvertierung abgeschlossen ist und alle Ausgangs-BOOL-Werte (`OUT_00` bis `OUT_07`) aktualisiert wurden.

### **Daten-Eingänge**
*   **IN** (Typ: `logiBUS::utils::conversion::types::ST08X`): Die Eingangsstruktur, die die acht zu extrahierenden BOOL-Werte enthält.

### **Daten-Ausgänge**
*   **OUT_00** (Typ: `BOOL`): Der erste extrahierte BOOL-Wert (Bit 00).
*   **OUT_01** (Typ: `BOOL`): Der zweite extrahierte BOOL-Wert (Bit 01).
*   **OUT_02** (Typ: `BOOL`): Der dritte extrahierte BOOL-Wert (Bit 02).
*   **OUT_03** (Typ: `BOOL`): Der vierte extrahierte BOOL-Wert (Bit 03).
*   **OUT_04** (Typ: `BOOL`): Der fünfte extrahierte BOOL-Wert (Bit 04).
*   **OUT_05** (Typ: `BOOL`): Der sechste extrahierte BOOL-Wert (Bit 05).
*   **OUT_06** (Typ: `BOOL`): Der siebte extrahierte BOOL-Wert (Bit 06).
*   **OUT_07** (Typ: `BOOL`): Der achte extrahierte BOOL-Wert (Bit 07).

### **Adapter**
Keine Adapter vorhanden.

## Funktionsweise
Sobald ein Ereignis am Eingang `REQ` empfangen wird, führt der Funktionsblock eine direkte Zuweisung der einzelnen BOOL-Komponenten der Eingangsstruktur `IN` zu den entsprechenden Ausgangsvariablen durch. Konkret wird `IN.X_00` dem Ausgang `OUT_00` zugewiesen, `IN.X_01` dem Ausgang `OUT_01` und so weiter bis `IN.X_07` an `OUT_07`. Nach erfolgreicher Zuweisung wird ein Bestätigungsereignis `CNF` am Ausgang ausgegeben, um anzuzeigen, dass die Ergebnisse verfügbar sind.

## Technische Besonderheiten
*   **Direkte Zuordnung:** Der Funktionsblock implementiert eine einfache und direkte 1:1-Zuordnung von den Feldern der `ST08X`-Struktur zu den einzelnen BOOL-Ausgängen.
*   **Typensicherheit:** Durch die Verwendung des spezifischen Typs `ST08X` wird eine klare und typensichere Schnittstelle gewährleistet.
*   **Effizienz:** Die Konvertierung ist hoch effizient, da keine komplexe Logik oder Berechnungen erforderlich sind.

## Zustandsübersicht
Dieser Funktionsblock ist zustandslos. Er speichert keine internen Daten zwischen Aufrufen und seine Ausgabe hängt ausschließlich von den aktuellen Eingangswerten ab. Jede Ausführung ist unabhängig von vorherigen Ausführungen.

## Anwendungsszenarien
*   **Zerlegung von kombinierten Signalen:** Ideal, um eine logisch gruppierte 8-Bit-Struktur in ihre einzelnen, unabhängigen BOOL-Signale aufzuteilen.
*   **Anpassung der Schnittstelle:** Ermöglicht die Anbindung an andere Funktionsblöcke oder Systeme, die einzelne BOOL-Eingänge anstelle einer Struktur erwarten.
*   **Visualisierung und Diagnose:** Vereinfacht die separate Anzeige oder Überwachung jedes einzelnen Bits einer `ST08X`-Struktur.

## Vergleich mit ähnlichen Bausteinen
Dieser Funktionsblock ist speziell für die `ST08X`-Struktur konzipiert. Während generische Bit-Extraktionsfunktionen (z.B. aus einem BYTE oder WORD) ähnliche Ergebnisse liefern könnten, bietet `ST08X_TO_BOOLS` eine klar definierte, typisierte Schnittstelle für die spezifische `ST08X`-Struktur. Dies erhöht die Lesbarkeit und vermeidet potenzielle Fehler bei der manuellen Bit-Indizierung. Er ist simpler und spezifischer als Bausteine, die komplexe Bitfeld-Operationen oder variable Bitanzahlen unterstützen.

## Fazit
Der Funktionsblock `ST08X_TO_BOOLS` ist ein nützliches Werkzeug zur Zerlegung von `ST08X`-Strukturen in individuelle BOOL-Signale. Er besticht durch seine Einfachheit, Effizienz und die klare, typensichere Schnittstelle, was die Entwicklung und Wartung von 4diac-Anwendungen vereinfacht.
