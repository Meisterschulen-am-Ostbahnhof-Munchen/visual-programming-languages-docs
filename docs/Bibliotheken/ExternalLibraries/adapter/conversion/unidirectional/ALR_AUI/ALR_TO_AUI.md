# ALR_TO_AUI


![ALR_TO_AUI](./ALR_TO_AUI.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **ALR_TO_AUI** ist ein zusammengesetzter Baustein (Composite FB), der einen LREAL-Wert, der über einen **ALR**-Adapter (unidirektional) anliegt, in einen UINT-Wert umwandelt und über einen **AUI**-Adapter (unidirektional) bereitstellt. Die Konvertierung erfolgt mittels des internen IEC‑61131‑Bausteins `F_LREAL_TO_UINT`. Der Baustein kapselt die Adapterwandlung und bietet eine saubere Schnittstelle für den Austausch zwischen den beiden Adaptertypen.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
Der FB besitzt keine eigenen Ereignis-Eingänge. Ereignisse werden indirekt über den **ALR_IN**-Adapter empfangen:
- **ALR_IN.E1** – Ereignis zur Auslösung der Konvertierung.

### **Ereignis-Ausgänge**
Der FB besitzt keine eigenen Ereignis-Ausgänge. Ereignisse werden über den **AUI_OUT**-Adapter gesendet:
- **AUI_OUT.E1** – Bestätigungsereignis nach erfolgter Konvertierung.

### **Daten-Eingänge**
Die Daten werden ebenfalls über den **ALR_IN**-Adapter bereitgestellt:
- **ALR_IN.D1** – Eingangswert vom Typ **LREAL** (gemäß ALR-Adapter).

### **Daten-Ausgänge**
Die konvertierten Daten werden über den **AUI_OUT**-Adapter ausgegeben:
- **AUI_OUT.D1** – Ausgangswert vom Typ **UINT** (gemäß AUI-Adapter).

### **Adapter**

| Bezeichnung | Typ | Richtung | Beschreibung |
|-------------|-----|----------|--------------|
| **ALR_IN** | `adapter::types::unidirectional::ALR` | Socket (Eingang) | Liefert den LREAL-Wert und das Trigger-Ereignis. |
| **AUI_OUT** | `adapter::types::unidirectional::AUI` | Plug (Ausgang) | Gibt den konvertierten UINT-Wert und das Bestätigungsereignis aus. |

## Funktionsweise

Der FB arbeitet als reine Übersetzungsschicht zwischen zwei Adaptern:

1. Ein eingehendes Ereignis am Socket **ALR_IN.E1** triggert den internen Konvertierungsbaustein `F_LREAL_TO_UINT` über dessen **REQ**-Eingang.
2. Gleichzeitig wird der Datenwert **ALR_IN.D1** an den **IN**-Eingang des Konvertierungsbausteins weitergeleitet.
3. Der interne Baustein führt die Typumwandlung von **LREAL** nach **UINT** aus und legt das Ergebnis an seinem **OUT**-Ausgang an.
4. Sobald die Konvertierung abgeschlossen ist, sendet der interne Baustein ein Bestätigungsereignis (**CNF**), welches an den Plug **AUI_OUT.E1** weitergegeben wird.
5. Gleichzeitig wird der konvertierte Wert (**OUT**) an den Datenausgang **AUI_OUT.D1** übergeben.

Der gesamte Ablauf ist ereignisgesteuert und erfolgt pro auslösendem Ereignis einmalig.

## Technische Besonderheiten

- **Adapter‑Kapselung:** Der Baustein verbindet zwei unterschiedliche Adaptertypen (ALR und AUI) und ermöglicht so eine typsichere Kommunikation zwischen Komponenten, die diese Adapter verwenden.
- **Unidirektionale Adapter:** Sowohl der Eingangs- als auch der Ausgangsadapter sind unidirektional ausgelegt, d.h. es gibt nur eine Daten- und Ereignisrichtung (Eingang → Ausgang).
- **Interne Konvertierung:** Die eigentliche Wandlung wird durch den standardisierten IEC‑61131‑Baustein `F_LREAL_TO_UINT` durchgeführt. Dadurch ist das Konvertierungsverhalten wohldefiniert und plattformunabhängig.
- **Keine Zuständigkeit:** Der Composite FB selbst besitzt keinen eigenen Zustandsautomaten. Das Verhalten wird vollständig durch den eingebetteten Baustein bestimmt.

## Zustandsübersicht

Da es sich um einen zusammengesetzten Baustein ohne eigenen ECC (Execution Control Chart) handelt, existiert kein interner Zustandsautomat. Der Ablauf wird durch die Ereignisverknüpfungen gesteuert:

- **IDLE:** Warten auf ein Ereignis am Socket **ALR_IN.E1**.
- **KONVERTIEREN:** Nach Empfang des Ereignisses wird die Konvertierung ausgelöst; der interne Baustein durchläuft seinen eigenen Zustandsautomaten (z.B. REQ → CNF).
- **AUSGABE:** Nach Abschluss der Konvertierung wird das Ausgangsereignis **AUI_OUT.E1** sowie der konvertierte Wert ausgegeben.

## Anwendungsszenarien

- **Anbindung von Sensoren/Aktoren:** Ein Sensor liefert einen LREAL-Wert (z.B. Temperatur, Druck), der über einen ALR-Adapter in eine SPS eingelesen wird. Für eine Anzeige oder Weitergabe an ein System, das nur Ganzzahlen (UINT) verarbeitet, wird der FB vorgeschaltet.
- **Adapter‑Migration:** In bestehenden Anlagen sollen Adapter von ALR auf AUI umgestellt werden, ohne die angeschlossenen Komponenten zu ändern. Der Baustein fungiert als Zwischenstück.
- **Test‑ und Simulationsumgebungen:** Erzeugung von UINT‑Werten aus LREAL‑Quellen für Testzwecke.

## Vergleich mit ähnlichen Bausteinen

| Baustein | Eingangstyp | Ausgangstyp | Beschreibung |
|----------|-------------|-------------|--------------|
| **ALR_TO_AUI** | ALR (LREAL) | AUI (UINT) | Adapter‑basierte Konvertierung LREAL→UINT. |
| `F_LREAL_TO_UINT` | LREAL | UINT | Reine Datenkonvertierung ohne Adapter. |
| `LREAL_TO_INT` | LREAL | INT | Konvertierung in einen vorzeichenbehafteten Integer. |

Im Gegensatz zu den reinen Datenwandlern arbeitet **ALR_TO_AUI** auf Adapterebene, sodass sowohl die Daten als auch die zugehörigen Ereignisse über die Adapterschnittstellen ausgetauscht werden. Dies vereinfacht die Integration in adapterbasierte Architekturen.

## Fazit

Der **ALR_TO_AUI**-Funktionsblock ist ein nützliches Werkzeug zur Umwandlung von LREAL‑Werten aus einem ALR‑Adapter in UINT‑Werte eines AUI‑Adapters. Durch die Kapselung der Konvertierung in einem Composite FB wird die Wiederverwendbarkeit erhöht und die Systemschnittstelle sauber definiert. Der Baustein eignet sich besonders für Anwendungen, in denen Adaptertypen harmonisiert oder angepasst werden müssen, ohne die interne Logik der angeschlossenen Komponenten zu verändern.