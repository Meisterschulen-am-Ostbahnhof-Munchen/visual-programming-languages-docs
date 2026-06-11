# A2X_SPLIT_7


![A2X_SPLIT_7](./A2X_SPLIT_7.svg)

* * * * * * * * * *
## Einleitung

Der Funktionsbaustein **A2X_SPLIT_7** dient dazu, ein eingehendes A2X-Adaptersignal auf sieben identische Ausgänge zu verteilen. Er wird als generischer FB (generic FB) bereitgestellt und ermöglicht eine effiziente Signalvervielfachung innerhalb von 4diac-IDE-Projekten.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
- Keine

### **Ereignis-Ausgänge**
- Keine

### **Daten-Eingänge**
- Keine

### **Daten-Ausgänge**
- Keine

### **Adapter**

| Typ | Name | Beschreibung |
|-----|------|--------------|
| A2X (Socket) | **IN** | Eingangsadapter für das zu verteilende A2X-Signal |
| A2X (Plug)   | **OUT1** … **OUT7** | Sieben Ausgangsadapter, die jeweils eine identische Kopie des Eingangssignals bereitstellen |

## Funktionsweise

Der Baustein leitet das am Adapter **IN** anliegende A2X-Signal unverändert an alle sieben Ausgangsadapter (**OUT1** bis **OUT7**) weiter. Es findet keine Manipulation der Daten statt – die Signale werden lediglich passiv vervielfältigt. Der FB ist rein adapterbasiert und benötigt weder Ereignis- noch Dateneingänge.

## Technische Besonderheiten

- **Generischer Baustein**: Der FB ist als generischer Typ (`GEN_A2X_SPLIT`) deklariert und kann in verschiedenen Kontexten wiederverwendet werden.
- **Unidirektionale Adapter**: Alle verwendeten A2X-Adapter sind vom Typ `unidirectional`, d.h. die Daten fließen nur in eine Richtung (vom Socket zum Plug).
- **Keine Ereignissteuerung**: Die Signalweitergabe erfolgt rein datenflussgesteuert ohne zusätzliche Ereignisse oder Zustände.
- **Einfach erweiterbar**: Durch Anpassung der XML-Definition können beliebig viele Ausgänge (z.B. 2, 4, 10) realisiert werden.

## Zustandsübersicht

Der FB besitzt keine eigene Zustandsmaschine (ECC). Die Ausgangssignale sind stets eine exakte Abbildung des Eingangssignals. Es gibt keine internen Zustände oder zeitlichen Verzögerungen.

## Anwendungsszenarien

- **Verteilen eines Sensor- oder Steuerungssignals** an mehrere parallele Funktionsbausteine oder Subsysteme.
- **Bereitstellung identischer Adapterdaten** für redundante Verarbeitungspfade (z.B. Sicherheitskopien).
- **Simulation oder Testaufbauten**, bei denen ein Signal mehrfach benötigt wird, ohne die Quelle mehrfach zu instanziieren.

## Vergleich mit ähnlichen Bausteinen

- **A2X_SPLIT_2, A2X_SPLIT_3, …** : Diese Bausteine verteilen das Eingangssignal auf zwei, drei bzw. mehr Ausgänge. Der vorliegende FB ist speziell auf sieben Ausgänge ausgelegt und kann als Spezialisierung eines generischen Split-Bausteins betrachtet werden.
- **Manuelle Vervielfachung per Verbindung**: Theoretisch könnte ein A2X-Signal durch mehrfaches Verbinden eines Ausgangs ebenfalls verteilt werden – der Split-FB sorgt jedoch für eine saubere, strukturierte und wiederverwendbare Lösung.

## Fazit

Der **A2X_SPLIT_7** ist ein einfacher, aber nützlicher Funktionsbaustein zur Signalvervielfachung in A2X-basierten Adaptersystemen. Durch seinen generischen Charakter und die klare Schnittstelle eignet er sich hervorragend für modulare Automatisierungslösungen mit der 4diac-IDE.