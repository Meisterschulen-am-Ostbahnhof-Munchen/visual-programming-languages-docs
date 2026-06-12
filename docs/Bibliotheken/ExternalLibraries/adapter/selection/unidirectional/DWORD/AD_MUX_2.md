# AD_MUX_2


![AD_MUX_2](./AD_MUX_2.svg)

* * * * * * * * * *

## Einleitung

Der Funktionsbaustein **AD_MUX_2** realisiert einen generischen Multiplexer für Adapter‑Schnittstellen vom Typ `adapter::types::unidirectional::AD`. Er wählt zwischen zwei Eingangsadaptern (IN1, IN2) basierend auf einem ganzzahligen Index K aus und leitet das ausgewählte Adaptersignal an den Ausgangsadapter OUT weiter. Die Auswahl wird durch einen Ereignisimpuls am Eingang REQ gestartet; nach erfolgreicher Umschaltung quittiert der Baustein dies mit einem Ereignis am Ausgang CNF.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| REQ  | Event | Set Index K |

### **Ereignis-Ausgänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| CNF  | Event | Confirmation of Set Index K |

### **Daten-Eingänge**

| Name | Typ | Kommentar |
|------|-----|-----------|
| K    | UINT | Index (0 = IN1, 1 = IN2) |

### **Daten-Ausgänge**

Keine eigenen Datenausgänge. Die Ausgabe erfolgt über den Adapter‑Plug OUT.

### **Adapter**

| Art      | Name | Typ                                      | Kommentar                          |
|----------|------|------------------------------------------|------------------------------------|
| Plug     | OUT  | adapter::types::unidirectional::AD       | Ausgang: enthält IN1 für K=0, IN2 für K=1 |
| Socket   | IN1  | adapter::types::unidirectional::AD       | Erster Eingang                    |
| Socket   | IN2  | adapter::types::unidirectional::AD       | Zweiter Eingang                   |

## Funktionsweise

Der Baustein arbeitet nach einem einfachen Selektionsprinzip:

1. Ein Ereignis am Eingang **REQ** aktiviert die Auswertung des Daten‑Eingangs **K**.
2. Der Wert von K bestimmt, welcher der beiden Adapter‑Sockets an den Adapter‑Plug **OUT** durchgeschaltet wird:
   - **K = 0** → OUT erhält die Daten/Signale von IN1.
   - **K = 1** → OUT erhält die Daten/Signale von IN2.
3. Nach erfolgter Umschaltung wird ein Bestätigungsereignis am Ausgang **CNF** ausgegeben.

Der Baustein selbst enthält keine interne Zustandsmaschine; er arbeitet streng ereignisgesteuert.

## Technische Besonderheiten

- **Generischer Baustein (generic FB)**: Der Baustein ist als generischer Funktionsbaustein deklariert. Die Adapter‑Typen sind über die Attribute `GenericClassName` und `TypeHash` gekennzeichnet, was eine Wiederverwendung mit verschiedenen, aber strukturgleichen Adapter‑Definitionen ermöglicht.
- **Adapter‑basiert**: Die Ein‑ und Ausgabe erfolgt ausschließlich über Adapter‑Schnittstellen. Dadurch können komplexe Datenstrukturen oder Signalbündel effizient weitergereicht werden, ohne dass einzelne Variablen deklariert werden müssen.
- **Ereignis‑gesteuerte Auswahl**: Die Umschaltung erfolgt nur auf ein explizites REQ‑Ereignis hin; Änderungen von K ohne Ereignis haben keine sofortige Wirkung.

## Zustandsübersicht

Der Baustein besitzt keinen programmierten Ablaufzustand. Er kann als **ereignisgesteuerter Transmitter** betrachtet werden:

- **Ruhezustand**: Kein Ereignis anstehend, OUT ist auf den zuletzt ausgewählten Adapter eingestellt.
- **Auswahlphase**: Nach REQ wird K gelesen und der entsprechende Adapter durchgeschaltet.
- **Bestätigungsphase**: Es wird CNF ausgegeben, danach kehrt der Baustein in den Ruhezustand zurück.

## Anwendungsszenarien

- **Umschaltung zwischen zwei Sensoren/Aktoren**: Wenn zwei unterschiedliche Geräte (z. B. verschiedene Messwertgeber) über denselben Kommunikationsadapter an eine Steuerung angebunden werden sollen.
- **Redundanz‑Umschaltung**: Wechsel zwischen primärem und sekundärem Signalpfad, gesteuert durch einen Fehler‑ oder Steuerindex.
- **Test‑/Normalbetrieb**: Auswahl zwischen einem normalen Betriebsadapter und einem Test‑/Simulationsadapter.

## Vergleich mit ähnlichen Bausteinen

- **MUX_2 (Standard‑Datentyp‑Multiplexer)**: Im Gegensatz zu einem klassischen Multiplexer, der elementare Datentypen (z. B. INT, BOOL) auswählt, arbeitet AD_MUX_2 auf Adapterebene. Der Vorteil liegt in der Bündelung mehrerer Signale und der typisierten Schnittstelle.
- **AD_MUX_N (N‑fach Multiplexer)**: Ein erweiterter Baustein mit mehr als zwei Eingängen (z. B. AD_MUX_4) würde mehrere Sockets und einen größeren Indexbereich benötigen. AD_MUX_2 stellt die einfachste Form dar.
- **Adapter‑Selektor mit Priorität**: Alternativ könnte ein Baustein mit Prioritätslogik (z. B. „erst gültiges Signal gewinnt“) realisiert werden; AD_MUX_2 folgt dagegen einer strikten Indexlogik.

## Fazit

Der **AD_MUX_2** ist ein kompakter, generischer Funktionsbaustein zur Adapter‑Auswahl in 4diac‑Umgebungen. Seine klare Ereignisschnittstelle und die Adapter‑basierte Arbeitsweise machen ihn ideal für Anwendungen, bei denen Signalpfade flexibel umgeschaltet werden müssen. Durch die generische Deklaration lässt er sich leicht in verschiedene Projekte integrieren oder an spezifische Adapter‑Typen anpassen.