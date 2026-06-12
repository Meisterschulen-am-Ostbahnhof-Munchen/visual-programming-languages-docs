# ALI_TO_AW


![ALI_TO_AW](./ALI_TO_AW.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **ALI_TO_AW** ist ein zusammengesetzter Baustein (Composite FB), der einen LINT-Wert (ALI-Adapter) in einen WORD-Wert (AW-Adapter) umwandelt. Er kapselt die Konvertierungslogik des IEC-61131-3-Funktionsbausteins `F_LINT_TO_WORD` in einer adapterbasierten Schnittstelle. Der Baustein ist für den Einsatz in unidirektionalen Adapter-Kommunikationspfaden vorgesehen und ermöglicht eine saubere Trennung von Datenformat und Anwendung.

## Schnittstellenstruktur

Der Baustein besitzt keine direkten Ereignis- oder Datenein-/ausgänge auf FB-Ebene. Die Kommunikation erfolgt ausschließlich über zwei Adapter (einen Socket und einen Plug).

### **Ereignis-Eingänge**  
*Keine direkten Ereignis-Eingänge vorhanden. Das eingehende Ereignis wird über den Adapter `ALI_IN.E1` bereitgestellt.*

### **Ereignis-Ausgänge**  
*Keine direkten Ereignis-Ausgänge vorhanden. Das ausgehende Ereignis wird über den Adapter `AW_OUT.E1` bereitgestellt.*

### **Daten-Eingänge**  
*Keine direkten Daten-Eingänge vorhanden. Der LINT-Wert wird über den Adapter `ALI_IN.D1` bezogen.*

### **Daten-Ausgänge**  
*Keine direkten Daten-Ausgänge vorhanden. Der WORD-Wert wird über den Adapter `AW_OUT.D1` ausgegeben.*

### **Adapter**

| Adapter-Name | Typ | Richtung | Kommentar |
|--------------|-----|----------|-----------|
| `ALI_IN` | `adapter::types::unidirectional::ALI` | Socket (Eingang) | LINT-Adapter-Eingang; liefert Ereignis auf `E1` und LINT-Daten auf `D1` |
| `AW_OUT` | `adapter::types::unidirectional::AW` | Plug (Ausgang) | WORD-Adapter-Ausgang; sendet Ereignis auf `E1` und WORD-Daten auf `D1` |

## Funktionsweise

1. Der Baustein erwartet über den Socket `ALI_IN` ein Ereignis (an `E1`) sowie einen zugehörigen LINT-Datenwert (an `D1`).  
2. Das Ereignis wird an den internen Konvertierungsbaustein `F_LINT_TO_WORD` (Typ `iec61131::conversion::F_LINT_TO_WORD`) weitergeleitet (Verbindung `ALI_IN.E1` → `Convert.REQ`). Gleichzeitig wird der LINT-Wert an den Dateneingang `IN` des Konverters übergeben (Verbindung `ALI_IN.D1` → `Convert.IN`).  
3. Der interne Baustein führt die Wandlung durch und signalisiert die Fertigstellung über seinen Ausgang `CNF`.  
4. Dieses Ereignis wird an den Plug `AW_OUT.E1` weitergegeben. Der konvertierte WORD-Wert (Ausgang `OUT` des Konverters) wird parallel an den Dateneingang `AW_OUT.D1` angelegt.  

Somit stellt der FB die vom Eingangsadapter bereitgestellten Daten in konvertierter Form am Ausgangsadapter zur Verfügung, gesteuert durch die Ereigniskette.

## Technische Besonderheiten

- **IEC-61131-3-Konvertierung**: Die eigentliche Umwandlung erfolgt mittels des standardisierten Funktionsbausteins `F_LINT_TO_WORD`, der eine verlustbehaftete Konvertierung von 64‑Bit (LINT) auf 16‑Bit (WORD) durchführt (Abschneiden oder Bereichsprüfung abhängig von der Implementierung).  
- **Adapterbasierte Schnittstelle**: Der Baustein ist vollständig in die Adaptertechnologie von 4diac eingebettet und eignet sich für unidirektionale Kommunikationspfade (package `adapter::conversion::unidirectional`).  
- **Versionierung**: Version 1.0, bereitgestellt unter der Eclipse Public License 2.0 (EPL‑2.0).  
- **Keine eigenen Zustände**: Der FB delegiert die Zustandslogik vollständig an den inneren `F_LINT_TO_WORD`.  

## Zustandsübersicht

Da es sich um einen zusammengesetzten Baustein handelt, besitzt `ALI_TO_AW` keinen eigenen Zustandsautomaten. Der interne Konverter `F_LINT_TO_WORD` realisiert typischerweise folgende implizite Zustände:

| Zustand | Beschreibung |
|---------|--------------|
| IDLE    | Warten auf ein Ereignis am Eingang `ALI_IN.E1`. |
| CONVERT | Nach Empfang von `REQ` wird die Konvertierung durchgeführt. |
| DONE    | Nach Abschluss der Konvertierung wird `CNF` aktiviert und der Ergebniswert am Ausgang bereitgestellt. |

Anschließend kehrt der interne Baustein in den IDLE-Zustand zurück.

## Anwendungsszenarien

- **Steuerungstechnik**: Umwandlung eines 64‑Bit Zählerstands (z. B. von einem Encoder) in einen 16‑Bit Wert für eine einfache Anzeige oder eine Wort‑basierte Schnittstelle.  
- **Datenkonsolidierung**: Einsatz in Adapter‑Ketten, wenn ein nachfolgender Baustein nur WORD‑Eingänge akzeptiert, die Quelle aber LINT‑Daten liefert.  
- **Test- und Simulationsumgebungen**: Erzeugung von WORD‑Daten aus LINT‑Testwerten zur Überprüfung von Adapter‑Kommunikationspfaden.  

## Vergleich mit ähnlichen Bausteinen

- **LINT_TO_DWORD / LINT_TO_BYTE**: Andere Konvertierungen mit unterschiedlicher Zielbreite; `ALI_TO_AW` ist speziell auf die Kombination der unidirektionalen Adapter `ALI` und `AW` zugeschnitten.  
- **Direkter Einsatz von F_LINT_TO_WORD**: `ALI_TO_AW` bietet eine höhere Abstraktionsebene durch Adapter‑Schnittstellen und erleichtert die Einbindung in adapterbasierte Architekturen, während der reine Funktionsbaustein nur über Ereignis‑ und Datenschnittstellen verfügt.  

## Fazit

Der Funktionsblock `ALI_TO_AW` ist ein praktischer und wiederverwendbarer Baustein zur Konvertierung von LINT‑ auf WORD‑Adaptern. Er kapselt die typische IEC-61131-3‑Wandlung in einer adapterfreundlichen Hülle und vereinfacht so die Integration in bestehende oder neue 4diac‑Projekte. Seine klare unidirektionale Schnittstelle und die Einhaltung des Eclipse‑Public‑License‑Modells machen ihn zu einer soliden Komponente für Automatisierungslösungen, die unterschiedliche Datenbreiten verbinden müssen.