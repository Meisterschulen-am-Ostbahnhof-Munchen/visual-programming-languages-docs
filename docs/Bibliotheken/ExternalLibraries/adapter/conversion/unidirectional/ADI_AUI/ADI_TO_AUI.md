# ADI_TO_AUI


![ADI_TO_AUI](./ADI_TO_AUI.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **ADI_TO_AUI** ist ein Composite-FB (zusammengesetzter Baustein), der eine Schnittstellenkonvertierung zwischen dem ADI-Adapter (DINT, 32‑Bit‑Ganzzahl) und dem AUI-Adapter (UINT, 16‑Bit‑Ganzzahl) realisiert. Er ermöglicht die unidirektionale Übertragung eines Wertes von einem DINT‑Adapter an einen UINT‑Adapter unter Verwendung eines standardisierten IEC 61131‑Konvertierungsbausteins.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Keine – die Ereignissteuerung erfolgt ausschließlich über die Adapter.

### **Ereignis-Ausgänge**
Keine.

### **Daten-Eingänge**
Keine – alle Daten werden über den Socket-Adapter bereitgestellt.

### **Daten-Ausgänge**
Keine – alle Daten werden über den Plug-Adapter ausgegeben.

### **Adapter**
| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| Socket | `ADI_IN` | Eingang | ADI-Adapter (DINT) – liefert den zu konvertierenden Wert und ein Ereignis |
| Plug   | `AUI_OUT` | Ausgang | AUI-Adapter (UINT) – stellt den konvertierten Wert und zugehöriges Ereignis bereit |

## Funktionsweise
Der Baustein besitzt keine eigenen Ein-/Ausgangs‑Ereignisse oder Datenpunkte auf der obersten Ebene. Die gesamte Steuerung und Datenübertragung erfolgt über die beiden Adapter:

1. **Ereignisweiterleitung**:  
   Das am Socket `ADI_IN` eingehende Ereignis `E1` wird direkt an den internen Baustein `F_DINT_TO_UINT` (Typ: `iec61131::conversion`) weitergeleitet, um eine Konvertierung zu triggern.

2. **Datenpfad**:  
   Der über `ADI_IN.D1` bereitgestellte DINT‑Wert wird an den Eingang `IN` des `F_DINT_TO_UINT` übergeben. Nach erfolgreicher Konvertierung liegt das Ergebnis (UINT) am Ausgang `OUT` an und wird auf den Datenausgang `D1` des Plug‑Adapters `AUI_OUT` gelegt.

3. **Rückmeldung**:  
   Der interne Baustein signalisiert das Ende der Konvertierung durch das Ereignis `CNF`. Dieses Ereignis wird auf das Ausgangsereignis `E1` des Plug‑Adapters `AUI_OUT` übertragen – synchron zum bereitgestellten Datenwert.

Damit realisiert der FB eine **unidirektionale, ereignisgesteuerte Übertragung** eines DINT‑Werts in einen UINT‑Wert über die Adapterschnittstellen.

## Technische Besonderheiten
- **Composite‑FB**: Der Baustein kapselt die Konvertierungslogik vollständig und bietet eine aufgeräumte, wiederverwendbare Schnittstelle.  
- **Verwendeter Kernbaustein**: `iec61131::conversion::F_DINT_TO_UINT` – eine standardisierte IEC 61131‑Funktion zur Umwandlung von DINT in UINT (Wertebereichsanpassung: DINT auf UINT wird ohne Vorzeichen betrachtet, negative Werte werden entsprechend umgesetzt).  
- **Adapter‑Typen**: Die Adapter `ADI` und `AUI` sind als unidirektionale Adapter definiert (`adapter::types::unidirectional`). Sie stellen jeweils ein Ereignispaar (`E1`/`E1`) und einen Datenpunkt (`D1` im entsprechenden Datentyp) bereit.  
- **Paket‑Struktur**: Der FB ist im Paket `adapter::conversion::unidirectional` organisiert.  
- **Lizenz**: Der Baustein unterliegt der Eclipse Public License 2.0 (EPL‑2.0). Copyright liegt bei der HR Agrartechnik GmbH.

## Zustandsübersicht
Als Composite‑FB besitzt **ADI_TO_AUI** keinen eigenen internen Zustandsautomaten. Der Zustand wird ausschließlich durch den eingebetteten Baustein `F_DINT_TO_UINT` bestimmt, der nach Erhalt des `REQ`‑Ereignisses die Konvertierung vornimmt und mit `CNF` abschließt. Der Baustein ist daher **zustandslos** im Sinne eines reinen Funktionsbausteins (keine speichernden Zustände außerhalb des Kernbausteins).

## Anwendungsszenarien
- **Schnittstellenanpassung** zwischen Systemkomponenten, die unterschiedliche Datentypen für analoge oder digitale Werte verwenden (z. B. Sensoren mit DINT‑Ausgabe und Aktoren mit UINT‑Eingabe).  
- **Datenkonsolidierung** in heterogenen IEC 61499‑Netzwerken, in denen Adapter unterschiedlicher Datentypen aufeinandertreffen.  
- **Prototypen und Migration**: Einfache Integration von Bausteinen, die ursprünglich mit DINT arbeiten, in eine Umgebung, die UINT erwartet – ohne manuelle Konvertierung in jedem Verbindungsschritt.

## Vergleich mit ähnlichen Bausteinen
Direkt vergleichbare Adapter‑Konvertierungsblöcke existieren für andere Datentypen (z. B. `BOOL_TO_UINT`, `INT_TO_DINT`). Der Unterschied von **ADI_TO_AUI** liegt in der spezifischen Kombination der Adapter‑Schnittstellen (ADI ↔ AUI). Im Gegensatz zu einfachen Konvertierungs‑FBs (`F_DINT_TO_UINT`) kapselt dieser Composite‑FB sowohl die Adapter‑Anbindung als auch die Ereignis‑ und Datensynchronisation in einem wiederverwendbaren Modul.

Ein alternatives Design könnte einen generischen Konvertierungsbaustein mit parametrierbaren Adaptertypen verwenden, jedoch bietet die dedizierte Lösung eine klarere Dokumentation und einfachere Handhabung in der 4diac‑IDE.

## Fazit
Der Funktionsblock **ADI_TO_AUI** bietet eine saubere, wartbare und standardisierte Möglichkeit, DINT‑Daten über einen ADI‑Adapter in ein UINT‑Signal über einen AUI‑Adapter umzuwandeln. Durch die Verwendung eines IEC 61131‑Kernbausteins ist die Konvertierung normkonform und zuverlässig. Der Composite‑Ansatz erhöht die Wiederverwendbarkeit und vereinfacht das Engineering in verteilten Automatisierungssystemen.