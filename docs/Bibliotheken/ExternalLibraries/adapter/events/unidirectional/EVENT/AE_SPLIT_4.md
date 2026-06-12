# AE_SPLIT_4


![AE_SPLIT_4](./AE_SPLIT_4.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AE_SPLIT_4** verteilt ein eingehendes Ereignis eines unidirektionalen **AE-Adapters** auf vier identische Ausgangsadapter. Er wird als generischer Baustein (Generic FB) ausgeführt und kann daher für beliebige Datentypen des Adapters verwendet werden. Die Verteilung erfolgt ohne Verzögerung oder Zustandsänderung – das ankommende Ereignis wird gleichzeitig an alle vier Ausgänge weitergeleitet.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
Der Funktionsblock besitzt keine expliziten Ereignis-Eingänge. Die Ereignissteuerung erfolgt ausschließlich über den Socket **IN** (siehe Abschnitt Adapter).

### **Ereignis-Ausgänge**
Der Funktionsblock besitzt keine expliziten Ereignis-Ausgänge. Die Ereignisweitergabe erfolgt über die Plugs **OUT1** bis **OUT4** (siehe Abschnitt Adapter).

### **Daten-Eingänge**
Keine.

### **Daten-Ausgänge**
Keine.

### **Adapter**
| Richtung | Name | Typ | Beschreibung |
|----------|------|-----|--------------|
| Socket (Eingang) | **IN** | `adapter::types::unidirectional::AE` | Empfängt ein unidirektionales Adapter-Ereignis (Ereignis + zugehörige Daten). |
| Plug (Ausgang) | **OUT1** | `adapter::types::unidirectional::AE` | Erster Ausgang – erhält das gleiche Ereignis und dieselben Daten wie am Eingang. |
| Plug (Ausgang) | **OUT2** | `adapter::types::unidirectional::AE` | Zweiter Ausgang. |
| Plug (Ausgang) | **OUT3** | `adapter::types::unidirectional::AE` | Dritter Ausgang. |
| Plug (Ausgang) | **OUT4** | `adapter::types::unidirectional::AE` | Vierter Ausgang. |

## Funktionsweise
Sobald am Socket **IN** ein Ereignis des AE-Adapters anliegt (mit allen zu diesem Ereignis gehörenden Daten), wird dieses Ereignis sofort und parallel an alle vier Plugs **OUT1**, **OUT2**, **OUT3** und **OUT4** weitergegeben. Die Ausgabe erfolgt zeitgleich – es gibt keine Prioritäten oder Sequenzen. Die Datentypen der Adapter sind aufgrund der generischen Auslegung des Bausteins frei wählbar (z. B. `INT`, `REAL`, `BOOL` etc.), solange alle beteiligten Adapter denselben Datentyp verwenden.

## Technische Besonderheiten
- **Generischer Baustein** – Der FB ist als generischer Typ (`GenericClassName = 'GEN_AE_SPLIT'`) realisiert. Dadurch kann der konkrete Datentyp des Adapters zur Projektierungszeit festgelegt werden.  
- **Unidirektionale Adapter** – Der Baustein arbeitet ausschließlich mit Adaptern des Typs `unidirectional::AE`. Rückkanäle oder bidirektionale Kommunikation werden nicht unterstützt.  
- **Lizenz** – Der Quellcode unterliegt der **Eclipse Public License 2.0** (EPL-2.0).  

## Zustandsübersicht
Der **AE_SPLIT_4** ist ein rein kombinatorischer Baustein und besitzt keine internen Zustände. Das Ausgangssignal hängt ausschließlich vom aktuellen Eingangssignal ab – es gibt keine Speicherung oder Verzögerung.

## Anwendungsszenarien
- **Sensorverteilung** – Ein einzelner Sensor (z. B. Temperatur, Drehzahl) liefert Daten über einen AE-Adapter; diese sollen an mehrere parallel arbeitende Steuerungsfunktionen verteilt werden.  
- **Signalweiterleitung in einer Steuerungskette** – Ein Ereignis muss mehrere nachgelagerte FBs parallel erreichen, z. B. zur Auslösung von Alarmen und Protokollierung.  
- **Multiplexing von Ereignisquellen** – (in Verbindung mit einem vorgeschalteten AE-MUX) können verschiedene Quellen auf die gleichen vier Ausgänge geschaltet werden.  

## Vergleich mit ähnlichen Bausteinen
- **E_SPLIT** – Standard-4diac-Baustein zur Verteilung eines Ereignisses auf mehrere Ereignisausgänge ohne Datenweitergabe. **AE_SPLIT_4** erweitert dies um die Fähigkeit, auch die zum Ereignis gehörenden Adapter-Daten mitzugeben.  
- **F_SPLIT** – Daten-Splitter (z. B. für IEC‑61131‑3 „MUX“) arbeiten meist nicht ereignisgesteuert. **AE_SPLIT_4** ist speziell für die ereignisbasierte Adapterkommunikation optimiert.  
- **AE_MERGE** – Der umgekehrte Baustein: fasst mehrere AE-Eingänge auf einen Ausgang zusammen.  

## Fazit
Der **AE_SPLIT_4** ist ein einfacher, aber leistungsfähiger Funktionsblock, der die ereignisgesteuerte Verteilung von Adapterdaten auf bis zu vier gleichberechtigte Ausgänge ermöglicht. Dank seiner generischen Auslegung kann er ohne Anpassung für beliebige Datentypen verwendet werden und eignet sich hervorragend für modulare, parallele Steuerungsarchitekturen.