import QtQuick 2.13
import QtQuick.Controls 2.12 as QQC2
import QtQuick.Controls.Material 2.3
import Fluid.Controls 1.0 as FluidControls
import Qt.labs.qmlmodels 1.0 as QQModels
import com.gecko.rr.models 1.0 as RRModels
import "../rrui" as RRUi
import "../singletons"

RRUi.DataTableView {
    id: stockReportTableView

    property alias busy: stockReportModel.busy
    property alias autoQuery: stockReportModel.autoQuery
    property Component buttonRow: null

    signal success(int successCode)
    signal error(int errorCode)

    function refresh() { stockReportModel.refresh(); }

    model: RRModels.StockReportModel {
        id: stockReportModel
        onSuccess: stockReportTableView.success(successCode);
        onError: stockReportTableView.error(errorCode);
    }

    QQC2.ScrollBar.vertical: RRUi.ScrollBar {
        policy: QQC2.ScrollBar.AlwaysOn
        visible: stockReportTableView.contentHeight > stockReportTableView.height
    }

    flickableDirection: TableView.VerticalFlick
    clip: true

    delegate: QQModels.DelegateChooser {
        QQModels.DelegateChoice {
            column: RRModels.StockReportModel.CategoryColumn
            delegate: RRUi.TableDelegate {
                implicitWidth: stockReportTableView.columnHeader.children[RRModels.StockReportModel.CategoryColumn].width
                implicitHeight: stockReportTableView.rowHeader.children[0].height

                FluidControls.SubheadingLabel {
                    anchors {
                        left: parent.left
                        right: parent.right
                        verticalCenter: parent.verticalCenter
                    }

                    horizontalAlignment: Qt.AlignLeft
                    verticalAlignment: Qt.AlignVCenter
                    text: category
                }
            }
        }

        QQModels.DelegateChoice {
            column: RRModels.StockReportModel.ItemColumn
            delegate: RRUi.TableDelegate {
                implicitWidth: stockReportTableView.columnHeader.children[RRModels.StockReportModel.ItemColumn].width
                implicitHeight: stockReportTableView.rowHeader.children[0].height

                FluidControls.SubheadingLabel {
                    anchors {
                        left: parent.left
                        right: parent.right
                        verticalCenter: parent.verticalCenter
                    }

                    horizontalAlignment: Qt.AlignLeft
                    verticalAlignment: Qt.AlignVCenter
                    text: item
                }
            }
        }

        QQModels.DelegateChoice {
            column: RRModels.StockReportModel.OpeningStockQuantityColumn
            delegate: RRUi.TableDelegate {
                implicitWidth: stockReportTableView.columnHeader.children[RRModels.StockReportModel.OpeningStockQuantityColumn].width
                implicitHeight: stockReportTableView.rowHeader.children[0].height

                FluidControls.SubheadingLabel {
                    anchors {
                        left: parent.left
                        right: parent.right
                        verticalCenter: parent.verticalCenter
                    }

                    horizontalAlignment: Qt.AlignRight
                    verticalAlignment: Qt.AlignVCenter
                    text: opening_stock_quantity + " " + unit
                }
            }
        }

        QQModels.DelegateChoice {
            column: RRModels.StockReportModel.QuantitySoldColumn
            delegate: RRUi.TableDelegate {
                implicitWidth: stockReportTableView.columnHeader.children[RRModels.StockReportModel.QuantitySoldColumn].width
                implicitHeight: stockReportTableView.rowHeader.children[0].height

                FluidControls.SubheadingLabel {
                    anchors {
                        left: parent.left
                        right: parent.right
                        verticalCenter: parent.verticalCenter
                    }

                    horizontalAlignment: Qt.AlignRight
                    verticalAlignment: Qt.AlignVCenter
                    text: quantity_sold + " " + unit
                }
            }
        }

        QQModels.DelegateChoice {
            column: RRModels.StockReportModel.QuantityBoughtColumn
            delegate: RRUi.TableDelegate {
                implicitWidth: stockReportTableView.columnHeader.children[RRModels.StockReportModel.QuantityBoughtColumn].width
                implicitHeight: stockReportTableView.rowHeader.children[0].height

                FluidControls.SubheadingLabel {
                    anchors {
                        left: parent.left
                        right: parent.right
                        verticalCenter: parent.verticalCenter
                    }

                    horizontalAlignment: Qt.AlignRight
                    verticalAlignment: Qt.AlignVCenter
                    text: quantity_bought + " " + unit
                }
            }
        }

        QQModels.DelegateChoice {
            column: RRModels.StockReportModel.QuantityInStockColumn
            delegate: RRUi.TableDelegate {
                implicitWidth: stockReportTableView.columnHeader.children[RRModels.StockReportModel.QuantityInStockColumn].width
                implicitHeight: stockReportTableView.rowHeader.children[0].height

                FluidControls.SubheadingLabel {
                    anchors {
                        left: parent.left
                        right: parent.right
                        verticalCenter: parent.verticalCenter
                    }

                    horizontalAlignment: Qt.AlignRight
                    verticalAlignment: Qt.AlignVCenter
                    text: quantity_in_stock + " " + unit
                }
            }
        }

        QQModels.DelegateChoice {
            column: RRModels.StockReportModel.ActionColumn
            delegate: RRUi.TableDelegate {
                implicitWidth: stockReportTableView.columnHeader.children[RRModels.StockReportModel.ActionColumn].width
                implicitHeight: stockReportTableView.rowHeader.children[0].height

                Loader {
                    readonly property var modelData: {
                        "client_id": model.client_id,
                        "transaction_id": model.transaction_id
                    }

                    anchors.centerIn: parent
                    sourceComponent: stockReportTableView.buttonRow
                }
            }
        }
    }
}
