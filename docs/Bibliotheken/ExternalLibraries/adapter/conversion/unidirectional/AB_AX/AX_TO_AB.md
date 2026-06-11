# AX_TO_AB


![AX_TO_AB](./AX_TO_AB.svg)

* * * * * * * * * *
## Einleitung

Der Composite-Funktionsblock `AX_TO_AB` dient zur Umwandlung eines BOOL-Adaptersignals vom Typ `AX` in ein BYTE-Adaptersignal vom Typ `AB`. Er kapselt die Typkonvertierung und das Durchreichen von Ereignissen in einer wiederverwendbaren Einheit.

## Schnittstellenstruktur

### **Ereignis-Eingänge**
| Name | Beschreibung |
|------|--------------|
| `E1` (aus `AX_IN`) | Ereigniseingang, der über den BOOL-Adapter empfangen und unverändert an den Ausgang weitergeleitet wird. |

### **Ereignis-Ausgänge**
| Name | Beschreibung |
|------|--------------|
| `E1` (aus `AB_OUT`) | Ereignisausgang, der das durchgereichte Ereignis vom Eingang bereitstellt. |

### **Daten-Eingänge**
| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| `D1` (aus `AX_IN`) | `BOOL` | Das zu konvertierende boolesche Signal (TRUE oder FALSE). |

### **Daten-Ausgänge**
| Name | Datentyp | Beschreibung |
|------|----------|--------------|
| `D1` (aus `AB_OUT`) | `BYTE` | Das konvertierte Signal: `TRUE` wird zu `1`, `FALSE` zu `0`. |

### **Adapter**
| Typ | Richtung | Bezeichner | Kommentar |
|-----|----------|------------|-----------|
| `adapter::types::unidirectional::AX` | Socket (Eingang) | `AX_IN` | BOOL-Adapter, der die Eingangsdaten und Ereignisse liefert. |
| `adapter::types::unidirectional::AB` | Plug (Ausgang) | `AB_OUT` | BYTE-Adapter, der die konvertierten Daten und Ereignisse ausgibt. |

## Funktionsweise

Der Funktionsblock besteht intern nur aus Verbindungen, die den Ereignis- und Datenpfad vom Socket `AX_IN` zum Plug `AB_OUT` durchschalten.  
- Das Ereignis `E1` wird ohne Verzögerung oder Veränderung weitergereicht.  
- Der Datenwert `D1` wird vom Typ `BOOL` in den Typ `BYTE` gewandelt. Dabei wird der boolesche Wert `TRUE` in das Byte `1` und `FALSE` in das Byte `0` umgesetzt. Die Konvertierung erfolgt implizit durch die Laufzeitumgebung von 4diac.

Da es sich um einen Composite-FB handelt, werden alle internen Verbindungen zur Entwurfszeit festgelegt; es gibt keine dynamische Logik oder Zustandsautomaten.

## Technische Besonderheiten

- **Composite-Typ**: Der Baustein ist ein reiner Netzwerk-FB ohne eigene Algorithmen. Die Konvertierung wird durch die Verbindung zweier unterschiedlicher Adaptertypen erreicht.  
- **Typkonvertierung**: Die Umwandlung von `BOOL` zu `BYTE` ist standardkonform und nutzt die implizite Cast-Funktion der 4diac-IDE. Dadurch entfällt der Einsatz eines separaten Konvertierungsbausteins.  
- **Versionierung**: Der FB ist mit Version `1.0` vom 17.02.2026 versehen und für die Nutzung im Package `adapter::conversion::unidirectional` vorgesehen.

## Zustandsübersicht

Der Baustein besitzt keine internen Zustände – er arbeitet rein kombinatorisch. Die Ausgangswerte sind zu jedem Zeitpunkt eine direkte Funktion der Eingangswerte.

## Anwendungsszenarien

- **Anbindung von Sensoren/Aktoren**: Wenn ein Gerät oder eine Steuerung als BOOL-Signal arbeitet, das Zielsystem aber ein BYTE-Adapterformat erwartet, kann `AX_TO_AB` als Vermittler eingesetzt werden.  
- **Adapterbrücken**: In heterogenen Automatisierungsnetzwerken, in denen unterschiedliche Adapterprotokolle verwendet werden, erlaubt der FB eine einfache und typsichere Verbindung.  
- **Test und Simulation**: Der FB kann als einfacher Konverter in Testumgebungen genutzt werden, um Signale zwischen verschiedenen Logikschichten zu übersetzen.

## Vergleich mit ähnlichen Bausteinen

Es existieren spezielle Konvertierungs-FBs wie `BOOL_TO_BYTE` oder `BYTE_TO_BOOL`, die jedoch meist als Basis-FBs (Basic Function Blocks) mit einem Algorithmus realisiert sind. Der `AX_TO_AB` ist dagegen ein Composite-FB auf Adapterebene und kapselt die gesamte (Ereignis- und Daten-) Kommunikation. Er ist dann sinnvoll, wenn ganze Adapterschnittstellen umgesetzt werden müssen, nicht nur einzelne Datenpunkte.

## Fazit

Der Composite-FB `AX_TO_AB` bietet eine kompakte und elegante Lösung zur Umwandlung eines BOOL-Adapter in einen BYTE-Adapter. Durch die implizite Typkonvertierung und die direkte Ereignisdurchleitung reduziert er den manuellen Anpassungsaufwand und erhöht die Wiederverwendbarkeit in modularen Automatisierungsprojekten.