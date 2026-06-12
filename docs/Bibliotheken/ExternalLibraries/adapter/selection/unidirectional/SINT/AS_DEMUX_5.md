# AS_DEMUX_5


![AS_DEMUX_5](./AS_DEMUX_5.svg)

* * * * * * * * * *
## Einleitung
Der Funktionsblock **AS_DEMUX_5** ist ein generischer Demultiplexer für das unidirektionale Adapter-Interface `adapter::types::unidirectional::AS`. Er leitet ein an seinem Socket **IN** anliegendes Signal (z. B. ein analoges Messsignal) abhängig von einem Index **K** auf einen von fünf Ausgangsadaptern **OUT1** bis **OUT5** weiter. Der Baustein ist speziell für den Einsatz in der Automatisierungstechnik, insbesondere im Bereich der Agrartechnik, konzipiert und kann über die Attribute `GenericClassName` und `TypeHash` an spezifische Anwendungen angepasst werden.

## Schnittstellenstruktur
### **Ereignis-Eingänge**
| Name | Typ   | Kommentar               |
|------|-------|-------------------------|
| REQ  | Event | Set Index K             |

### **Ereignis-Ausgänge**
| Name | Typ   | Kommentar                       |
|------|-------|---------------------------------|
| CNF  | Event | Confirmation of Set Index K     |

### **Daten-Eingänge**
| Name | Typ  | Kommentar |
|------|------|-----------|
| K    | UINT | Index     |

### **Daten-Ausgänge**
Der FB besitzt keine direkten Datenausgänge. Die Ausgaben erfolgen über die Adapter-Plugs.

### **Adapter**
**Socket (Eingang)**
| Name | Typ                                      | Kommentar                    |
|------|------------------------------------------|------------------------------|
| IN   | `adapter::types::unidirectional::AS`     | Input Value to demultiplex   |

**Plugs (Ausgänge)**
| Name | Typ                                      | Kommentar |
|------|------------------------------------------|-----------|
| OUT1 | `adapter::types::unidirectional::AS`     |           |
| OUT2 | `adapter::types::unidirectional::AS`     |           |
| OUT3 | `adapter::types::unidirectional::AS`     |           |
| OUT4 | `adapter::types::unidirectional::AS`     |           |
| OUT5 | `adapter::types::unidirectional::AS`     |           |

## Funktionsweise
Der FB arbeitet nach dem Demultiplex-Prinzip:  
1. Ein gültiger Wert (z. B. ein analoges Signal) liegt am Socket **IN** an.  
2. Über den Ereigniseingang **REQ** wird der am Dateneingang **K** angelegte Index (0 … 4) übernommen.  
3. Der FB verbindet daraufhin den eingehenden Adapter **IN** mit dem entsprechenden Ausgangsadapter **OUTx** (x = K+1).  
4. Nach erfolgreicher Umschaltung wird das Ereignis **CNF** ausgegeben, um den Vorgang zu bestätigen.

Der Wert von **K** bestimmt den aktiven Kanal:  
- K=0 → OUT1  
- K=1 → OUT2  
- …  
- K=4 → OUT5  

Werte außerhalb des zulässigen Bereichs werden ignoriert oder führen zu keiner Umschaltung (implementierungsabhängig).

## Technische Besonderheiten
- **Generischer Aufbau**: Über das Attribut `GenericClassName = 'GEN_AS_DEMUX'` kann der FB als Vorlage für beliebig viele Ausgangskanäle verwendet werden. Die hier vorliegende Instanz `AS_DEMUX_5` ist eine spezielle Ausprägung mit fünf Ausgängen.
- **Unidirektionale Adapter**: Der Baustein arbeitet ausschließlich mit unidirektionalen `AS`-Adaptern, was eine gerichtete Datenübertragung vom Eingang zu einem Ausgang garantiert.
- **Kein interner Zustandsspeicher**: Die Umschaltung erfolgt ereignisgesteuert; nach der CNF-Quittierung kann sofort ein neuer Index verarbeitet werden.

## Zustandsübersicht
Der FB besitzt keine explizite Zustandsmaschine (kein ECC im XML). Das Verhalten ist streng ereignisgesteuert:
- **Idle**: Warten auf REQ.
- **Processing**: Bei REQ wird K ausgewertet und die Adapter-Verbindung geschaltet.
- **Done**: Nach Abschluss wird CNF gesendet, danach Rückkehr in Idle.

## Anwendungsszenarien
- **Landtechnische Steuerungen**: Verteilung eines analogen Sensorsignals (z. B. Drehmoment, Druck) auf verschiedene Aktoren oder Anzeigegeräte.
- **Industrielle Automatisierung**: Umschaltung zwischen mehreren Messstellen oder Datenquellen in einer Produktionslinie.
- **Test- und Prüfstände**: Selektives Ansteuern verschiedener Prüflinge über ein gemeinsames Signalinterface.

## Vergleich mit ähnlichen Bausteinen
- **AS_DEMUX_2, AS_DEMUX_3, …**: Bausteine mit weniger Ausgängen (2, 3, …). Die Funktionsweise ist identisch, lediglich die Anzahl der OUT-Plugs variiert.
- **AS_SELECT (Multiplexer)**: Führt die umgekehrte Operation aus – mehrere Eingänge auf einen Ausgang.
- **Direkte Variablenumschaltung**: Alternativ könnte ein Multiplexer über Data-Variablen realisiert werden. Der Adapter-Ansatz bietet jedoch eine saubere Interface-Kapselung und Wiederverwendbarkeit.

## Fazit
Der Funktionsblock **AS_DEMUX_5** stellt eine flexible und robuste Lösung zur kanalselektiven Weiterleitung von Adapter-Signalen dar. Seine generische Natur erlaubt eine einfache Anpassung an verschiedene Anforderungen, während die klare Ereignisschnittstelle eine zuverlässige und nachvollziehbare Steuerung ermöglicht. Durch die Einhaltung des IEC 61499‑Standards eignet er sich besonders für modulare Automatisierungsprojekte, in denen Wiederverwendbarkeit und Typsicherheit im Vordergrund stehen.