# AW_SPLIT_6

Bild nicht verfügbar


![AW_SPLIT_6](./AW_SPLIT_6.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsblock **AW_SPLIT_6** dient dazu, einen eingehenden unidirektionalen **AW**-Adapter auf sechs identische Ausgangs-Adapter aufzuteilen. Er ist als generischer Baustein konzipiert, der in der 4diac-IDE zur Verteilung von AW-Signalen verwendet wird. Der Baustein ist für Anwendungen gedacht, bei denen ein Signalwert – z. B. ein analoger oder digitaler Wert – mehrfach parallel benötigt wird, ohne dass eine manuelle Vervielfältigung der Verbindungen erfolgen muss.

## Schnittstellenstruktur

### **Ereignis-Eingänge**

Keine

### **Ereignis-Ausgänge**

Keine

### **Daten-Eingänge**

Keine

### **Daten-Ausgänge**

Keine

### **Adapter**

| Typ | Name | Richtung | Beschreibung |
|-----|------|----------|--------------|
| `adapter::types::unidirectional::AW` | IN | Socket | Eingangs-Adapter für das zu verteilende AW-Signal |
| `adapter::types::unidirectional::AW` | OUT1 – OUT6 | Plugs | Sechs Ausgangs-Adapter, die jeweils eine identische Kopie des Eingangssignals bereitstellen |

## Funktionsweise

Der Baustein empfängt über den Socket **IN** ein unidirektionales **AW**-Signal. Dieses Signal wird intern auf alle sechs Ausgangs-Plugs (**OUT1** bis **OUT6**) dupliziert. Die Weiterleitung erfolgt ohne Verzögerung oder Datenmanipulation – der Wert des eingehenden Adapters wird auf jedem der sechs Ausgänge direkt verfügbar gemacht. Der Baustein besitzt keine eigene Zustandslogik oder Ereignissteuerung; er arbeitet rein passiv und leitet das Signal durch.

## Technische Besonderheiten

- **Generischer Typ**: Der Baustein ist als generischer Funktionsblock (`GEN_AW_SPLIT`) implementiert, was eine flexible Wiederverwendung in verschiedenen Projekten erlaubt.
- **Typ-Hash**: Die Type‑Hash-Eigenschaft ist leer, was bedeutet, dass bei der Instanziierung keine automatische Überprüfung auf Typidentität erfolgt.
- **Keine Event‑ oder Daten‑Ports**: Die gesamte Signalweitergabe erfolgt ausschließlich über Adapter. Ereignisse werden nicht verarbeitet; daher eignet sich der Baustein nur für reine Datenweitergabe ohne zeitliche Steuerung.

## Zustandsübersicht

Der Funktionsblock besitzt keine internen Zustände. Er ist ein reiner Split‑Baustein ohne sequenzielle Logik. Das Verhalten ist deterministisch und jederzeit identisch: Das Eingangssignal wird auf alle Ausgänge kopiert.

## Anwendungsszenarien

- **Verteilung eines analogen Messwerts** an mehrere Verbraucher (z. B. Anzeigen, Regler, Aufzeichnungssysteme)
- **Aufteilung eines digitalen Steuersignals** auf parallele Aktor– oder Sensor‑Schnittstellen
- **Sternförmige Signalverteilung** in modularen Steuerungsarchitekturen, bei denen eine Quelle mehrere Senken versorgt

## Vergleich mit ähnlichen Bausteinen

Im Vergleich zu einem **AW_SPLIT_2** oder **AW_SPLIT_4** bietet der vorliegende Baustein eine höhere Anzahl von Ausgängen (6). Damit eignet er sich besonders für Systeme mit vielen parallelen Empfängern. Alternativ könnte eine Kaskadierung mehrerer kleiner Split‑Bausteine verwendet werden, was jedoch die Übersichtlichkeit und Performance beeinträchtigen kann. Der **AW_SPLIT_6** ist als Komplettlösung für diese Anforderung optimiert.

## Fazit

Der **AW_SPLIT_6** ist ein einfacher, aber nützlicher Funktionsblock zur Vervielfältigung eines unidirektionalen AW‑Signals auf sechs Ausgänge. Durch seine generische Natur und die Adapter‑basierte Schnittstelle fügt er sich nahtlos in eine 4diac‑Umgebung ein. Er empfiehlt sich für alle Anwendungen, bei denen ein einzelnes Signal ohne Umwege mehrfach benötigt wird.