# ADI_TO_AL


![ADI_TO_AL](./ADI_TO_AL.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock `ADI_TO_AL` dient als Composite-Baustein zur Konvertierung eines ADI-Adapters (DINT) in einen AL-Adapter (LWORD). Er kapselt eine Typumwandlung von einem 32‑Bit‑Ganzzahlwert in ein 64‑Bit‑Wort und stellt die Verbindung über unidirektionale Adapter bereit. Der Baustein ist ideal für Systeme, in denen eine unterschiedliche Datentypdarstellung zwischen Komponenten überbrückt werden muss.

## Schnittstellenstruktur
Der Baustein besitzt keine direkten Ereignis- oder Datenein-/-ausgänge. Die gesamte Kommunikation erfolgt über zwei Adapter-Schnittstellen:

### **Ereignis-Eingänge**
- **Keine direkten Ereignis-Eingänge**  
  Das Ereignis wird über den ADI‑Adapter `ADI_IN.E1` empfangen.

### **Ereignis-Ausgänge**
- **Keine direkten Ereignis-Ausgänge**  
  Das ausgehende Ereignis wird über den AL‑Adapter `AL_OUT.E1` gesendet.

### **Daten-Eingänge**
- **Keine direkten Daten-Eingänge**  
  Die Eingangsdaten werden über den ADI‑Adapter `ADI_IN.D1` (Datentyp: DINT) geliefert.

### **Daten-Ausgänge**
- **Keine direkten Daten-Ausgänge**  
  Die Ausgangsdaten werden über den AL‑Adapter `AL_OUT.D1` (Datentyp: LWORD) bereitgestellt.

### **Adapter**
| Bezeichnung | Typ | Richtung | Kommentar |
|-------------|-----|----------|-----------|
| `ADI_IN`    | `adapter::types::unidirectional::ADI` | Socket (Eingang) | Liefert einen DINT-Wert und steuert die Verarbeitung über Ereignis `E1`. |
| `AL_OUT`    | `adapter::types::unidirectional::AL`  | Plug (Ausgang)   | Gibt den konvertierten LWORD-Wert aus und quittiert über Ereignis `E1`. |

## Funktionsweise
Der Baustein implementiert eine einfache Typumwandlungskette:
1. Ein über den ADI‑Adapter `ADI_IN` eingehendes Ereignis ( `E1` ) startet die Konvertierung.
2. Der interne Funktionsblock `F_DINT_TO_LWORD` wandelt den eingehenden DINT‑Wert (`ADI_IN.D1`) in einen LWORD‑Wert um.
3. Nach erfolgreicher Konvertierung wird das Ergebnis als LWORD über den AL‑Adapter (`AL_OUT.D1`) ausgegeben und ein Ereignis (`E1`) gesendet.

Die Kommunikation zwischen den Adaptern und dem Konvertierungsbaustein erfolgt asynchron über Ereignis- und Datenverbindungen im Netzwerk des Composite-Blocks.

## Technische Besonderheiten
- **Unidirektionale Adapter** – Der Baustein verwendet ausschließlich unidirektionale Adapter (Socket für Eingang, Plug für Ausgang), die eine klare Datenflussrichtung vorgeben.
- **Interne Konvertierung** – Die eigentliche Typumwandlung wird durch den Standardbaustein `F_DINT_TO_LWORD` aus der IEC‑61131‑Bibliothek realisiert, sodass keine eigene Implementierung notwendig ist.
- **Lizenz** – Der Baustein ist unter der Eclipse Public License 2.0 (EPL‑2.0) lizenziert und kann frei verwendet, modifiziert und weitergegeben werden.
- **Keine Zustände** – Der Composite‑Baustein besitzt keine eigene Zustandslogik; die gesamte Steuerung erfolgt über die Ereignisverkettung.

## Zustandsübersicht
Der Baustein hat keine eigene Zustandsmaschine. Sein Verhalten ist rein reaktiv: Auf ein eingehendes Ereignis am ADI‑Adapter wird unverzögert das Ergebnis am AL‑Adapter ausgegeben. Interne Verzögerungen sind nicht definiert.

## Anwendungsszenarien
- **Datenbrücke zwischen unterschiedlichen Bussystemen** – Wenn ein Sensor oder eine Steuerung einen DINT‑Wert liefert, aber eine nachfolgende Komponente einen LWORD‑Wert erwartet (z. B. bei 64‑Bit‑Aktoren oder Feldbus‑Schnittstellen).
- **Middleware‑Anpassung** – Einsatz in heterogenen Automatisierungssystemen, um Adapter‑Typen ohne Änderung der ursprünglichen Komponenten zu harmonisieren.
- **Test- und Simulationsumgebungen** – Einfaches Umwandeln von Datentypen für Debugging‑ oder Ersatzverbindungen.

## Vergleich mit ähnlichen Bausteinen
- **Einzelkonvertierungs‑FBs** – Bausteine wie `DINT_TO_LWORD` (Direktkonvertierung ohne Adapter) bieten eine kompaktere Schnittstelle, erfordern aber eigene Ereignis‑ und Datenleitungen.  
- **Universelle Adapter‑Konverter** – Es existieren generische Konverter, die beliebige Datentypen via Adapter umwandeln. `ADI_TO_AL` ist speziell auf die Kombination DINT→LWORD optimiert und daher einfacher zu verstehen und zu warten.
- **Bidirektionale Adapter** – Im Gegensatz zu bidirektionalen Varianten beschränkt sich dieser Baustein auf eine Datenflussrichtung, was die Fehleranfälligkeit reduziert.

## Fazit
Der `ADI_TO_AL`‑Baustein bietet eine saubere, auf wenige Elemente reduzierte Lösung zur Typumwandlung von DINT nach LWORD über unidirektionale Adapter. Er ist leicht in bestehende 4diac‑Projekte integrierbar, benötigt keine eigenen Zustandsmodellierungen und profitiert von der Wiederverwendbarkeit des internen Standard‑Konvertierungsbausteins. Damit eignet er sich hervorragend für alle Anwendungen, bei denen eine schnelle und zuverlässige Datenanpassung zwischen unterschiedlichen Adapter‑Typen erforderlich ist.