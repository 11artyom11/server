#include "io_unit.h"

using namespace iounit;

/**
 * @brief Construct a new IOModel::IOModel object
 * 
 */
IOModel::IOModel()
{
    this->m_handler = std::make_unique <Client::Handler>();
    m_handler.get()->commap_init();
}

Handler_shrd_ptr IOModel::get_handler(void) const
{
    return m_handler;
}


/**
 * @brief Destroy the IOModel::IOModel object
 * 
 */
IOModel::~IOModel()
{
    
}