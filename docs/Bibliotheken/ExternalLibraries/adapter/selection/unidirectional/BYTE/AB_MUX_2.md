# AB_MUX_2

---

## Einleitung


![AB_MUX_2](./AB_MUX_2.svg)

Der Funktionsbaustein **AB_MUX_2** ist ein generischer Multiplexer, der zwei an Adapter-Schnittstellen anliegende Werte (IN1, IN2) über einen Index `K` auswählt und an den Ausgang `OUT` weiterleitet. Der Baustein arbeitet ereignisgesteuert und eignet sich für den Einsatz in industriellen Steuerungsanwendungen mit standardisierten Adaptern des Typs `AB`.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `REQ`    | Startet die Umschaltung: Der Index `K` wird ausgewertet und das entsprechende Eingangssignal an `OUT` übergeben. |

### **Ereignis-Ausgänge**

| Ereignis | Beschreibung |
|----------|--------------|
| `CNF`    | Bestätigt die erfolgreiche Ausführung der Umschaltung. |

### **Daten-Eingänge**

| Variable | Typ   | Beschreibung |
|----------|-------|--------------|
| `K`      | UINT  | Auswahlindex: 0 → IN1, 1 → IN2 (andere Werte verhalten sich undefiniert oder bleiben unverändert). |

### **Daten-Ausgänge**
Keine direkten Datenausgänge – die Ausgabe erfolgt ausschließlich über den Adapter `OUT`.

### **Adapter**

| Typ | Name | Beschreibung |
|-----|------|--------------|
| **Plug** | `OUT` | Adapter vom Typ `adapter::types::unidirectional::AB` – liefert das ausgewählte Signal. |
| **Socket** | `IN1` | Adapter vom Typ `adapter::types::unidirectional::AB` – erste Eingangsquelle. |
| **Socket** | `IN2` | Adapter vom Typ `adapter::types::unidirectional::AB` – zweite Eingangsquelle. |

## Funktionsweise

1. Der Baustein wartet im Ruhezustand auf ein `REQ`-Ereignis.
2. Beim Eintreffen von `REQ` wird der Wert des Daten-Eingangs `K` gelesen.
   - Ist `K = 0`, wird das Signal von Adapter `IN1` auf den Ausgangsadapter `OUT` geschaltet.
   - Ist `K = 1`, wird das Signal von Adapter `IN2` auf `OUT` geschaltet.
3. Nach erfolgreicher Umschaltung wird das Ereignis `CNF` ausgegeben.

Die Übertragung der Werte erfolgt über die standardisierten AB-Adapter, sodass der Baustein unabhängig von konkreten Datenformaten einsetzbar ist.

## Technische Besonderheiten

- **Generischer Aufbau**: Der Baustein ist als generischer FB (`GEN_AB_MUX`) deklariert und kann in unterschiedlichen Kontexten wiederverwendet werden.
- **Adapter-basiert**: Ein- und Ausgänge nutzen den Adaptertyp `unidirectional::AB`, der eine einheitliche Schnittstelle für wertebasierte Verbindungen bietet.
- **Keine Zustandsmaschine**: Der FB besitzt keinen expliziten ECC‑Zustandsautomaten – die einfache Logik wird direkt bei Empfang von `REQ` abgearbeitet.

## Zustandsübersicht

Da der Baustein keine Zustandsmaschine definiert (ECC fehlt), existiert nur der implizite **Idle**‑Zustand. Bei jedem `REQ` wird die Umschaltung sofort durchgeführt und `CNF` zurückgegeben. Es können keine verzögerten oder mehrstufigen Abläufe beobachtet werden.

## Anwendungsszenarien

- **Signalumschaltung** in Feldgeräten: Auswahl zwischen zwei Sensoren (z. B. Temperatur, Druck) unter Steuerung eines Index.
- **Redundanzumschaltung**: Wechsel zwischen primärem und sekundärem Messwert.
- **Betriebsartwahl**: Auswahl unterschiedlicher Regelparameter oder Steuerbefehle je nach Betriebsmodus.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Eigenschaft |
|----------|-------------|
| **AB_MUX_2** | Adapter‑basiert, zwei Eingänge, ereignisgesteuert, generisch. |
| Standard‑MUX‑Bausteine (z. B. MUX2) | Arbeitet meist mit direkten Daten‑Eingängen (BOOL, INT) und besitzt eigene Daten‑Ausgänge. |
| **Vorteil AB_MUX_2** | Einheitliche Adapter‑Schnittstelle, leichte Austauschbarkeit der Datenquelle und -senke. |

## Fazit

Der Funktionsbaustein **AB_MUX_2** stellt eine flexible und standardisierte Lösung zur Auswahl zwischen zwei Signalquellen dar. Die Verwendung von Adaptern erleichtert die Integration in komplexe 4diac‑Projekte und sorgt für eine saubere Trennung von Steuerlogik und Datenflüssen. Durch die generische Deklaration ist der Baustein wiederverwendbar und für eine Vielzahl industrieller Anwendungen geeignet.